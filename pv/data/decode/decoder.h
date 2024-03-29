/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
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

#ifndef PULSEVIEW_PV_DATA_DECODE_DECODER_H
#define PULSEVIEW_PV_DATA_DECODE_DECODER_H

#include <map>

#include <boost/shared_ptr.hpp>

#include <glib.h>

struct srd_decoder;
struct srd_decoder_inst;
struct srd_probe;
struct srd_session;

namespace pv {

namespace view {
class LogicSignal;
}

namespace data {
namespace decode {

class Decoder
{
public:
	Decoder(const srd_decoder *const decoder);

	virtual ~Decoder();

	const srd_decoder* decoder() const;

	bool shown() const;
	void show(bool show = true);

	const std::map<const srd_probe*,
		boost::shared_ptr<view::LogicSignal> >& probes() const;
	void set_probes(std::map<const srd_probe*,
		boost::shared_ptr<view::LogicSignal> > probes);

	const std::map<std::string, GVariant*>& options() const;

	void set_option(const char *id, GVariant *value);

	bool have_required_probes() const;

	srd_decoder_inst* create_decoder_inst(
		srd_session *const session) const;

private:
	const srd_decoder *const _decoder;

	bool _shown;

	std::map<const srd_probe*, boost::shared_ptr<pv::view::LogicSignal> >
		_probes;
	std::map<std::string, GVariant*> _options;
};

} // namespace decode
} // namespace data
} // namespace pv

#endif // PULSEVIEW_PV_DATA_DECODE_DECODER_H
