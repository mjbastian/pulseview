/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_VIEW_ANALOGSIGNAL_H
#define PULSEVIEW_PV_VIEW_ANALOGSIGNAL_H

#include "signal.h"

#include <boost/shared_ptr.hpp>

namespace pv {

namespace data {
class Analog;
class AnalogSnapshot;
}

namespace view {

class AnalogSignal : public Signal
{
private:
	static const QColor SignalColours[4];

	static const float EnvelopeThreshold;

public:
	AnalogSignal(pv::SigSession &session, sr_probe *const probe,
		boost::shared_ptr<pv::data::Analog> data);

	virtual ~AnalogSignal();

	boost::shared_ptr<pv::data::SignalData> data() const;

	boost::shared_ptr<pv::data::Analog> analog_data() const;

	void set_scale(float scale);

	/**
	 * Paints the background layer of the signal with a QPainter
	 * @param p the QPainter to paint into.
	 * @param left the x-coordinate of the left edge of the signal.
	 * @param right the x-coordinate of the right edge of the signal.
	 **/
	void paint_back(QPainter &p, int left, int right);

	/**
	 * Paints the mid-layer of the signal with a QPainter
	 * @param p the QPainter to paint into.
	 * @param left the x-coordinate of the left edge of the signal.
	 * @param right the x-coordinate of the right edge of the signal.
	 **/
	void paint_mid(QPainter &p, int left, int right);

private:
	void paint_trace(QPainter &p,
		const boost::shared_ptr<pv::data::AnalogSnapshot> &snapshot,
		int y, int left, const int64_t start, const int64_t end,
		const double pixels_offset, const double samples_per_pixel);

	void paint_envelope(QPainter &p,
		const boost::shared_ptr<pv::data::AnalogSnapshot> &snapshot,
		int y, int left, const int64_t start, const int64_t end,
		const double pixels_offset, const double samples_per_pixel);

private:
	boost::shared_ptr<pv::data::Analog> _data;
	float _scale;
};

} // namespace view
} // namespace pv

#endif // PULSEVIEW_PV_VIEW_ANALOGSIGNAL_H
