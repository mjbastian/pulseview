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

#ifndef PULSEVIEW_PV_MAINWINDOW_H
#define PULSEVIEW_PV_MAINWINDOW_H

#include <list>

#include <boost/weak_ptr.hpp>

#include <QMainWindow>

#include "sigsession.h"

struct srd_decoder;

class QVBoxLayout;

namespace pv {

class DeviceManager;

namespace toolbars {
class ContextBar;
class SamplingBar;
}

namespace view {
class View;
}

namespace widgets {
class DecoderMenu;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(DeviceManager &device_manager,
		const char *open_file_name = NULL,
		QWidget *parent = 0);

private:
	void setup_ui();

	void session_error(const QString text, const QString info_text);

	/**
	 * Updates the device list in the sampling bar, and updates the
	 * selection.
	 * @param selected_device The device to select, or NULL if the
	 * first device in the device list should be selected.
	 */
	void update_device_list(
		struct sr_dev_inst *selected_device = NULL);

private slots:
	void load_file(QString file_name);


	void show_session_error(
		const QString text, const QString info_text);

	void on_actionOpen_triggered();
	void on_actionSaveAs_triggered();
	void on_actionQuit_triggered();

	void on_actionConnect_triggered();

	void on_actionViewZoomIn_triggered();

	void on_actionViewZoomOut_triggered();

	void on_actionViewZoomFit_triggered();

	void on_actionViewZoomOneToOne_triggered();

	void on_actionViewShowCursors_triggered();

	void on_actionAbout_triggered();

	void add_decoder(srd_decoder *decoder);

	void run_stop();

	void capture_state_changed(int state);

private:
	DeviceManager &_device_manager;

	SigSession _session;

	pv::view::View *_view;

	QWidget *_central_widget;
	QVBoxLayout *_vertical_layout;

	toolbars::SamplingBar *_sampling_bar;
};

} // namespace pv

#endif // PULSEVIEW_PV_MAINWINDOW_H
