/***********************************************************************************
* Smooth Tasks
* Copyright (C) 2009 Mathias Panzenböck <grosser.meister.morti@gmx.net>
* Copyright (C) 2012 Sébastien Lambert <opensc@beonis.fr>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
***********************************************************************************/

#include "SmoothTasks/ToggleAnimation.h"

#include <Plasma/Animator>

namespace SmoothTasks {

void ToggleAnimation::init() {
	connect(
		&m_scrollAnimation, SIGNAL(finished()),
		this, SLOT(sfinished()));
}

void ToggleAnimation::stop() {
	m_scrollAnimation.stop();
}

void ToggleAnimation::start(Direction direction, int duration) {
	if (direction == Up) {
		startUp(duration);
	}
	else {
		startDown(duration);
	}
}

void ToggleAnimation::startUp( int duration) {
	if (m_direction == Up ) {
		return;
	}
	m_direction = Up;
	start(duration * (qreal(1.0) - m_value));
}

void ToggleAnimation::startDown(int duration) {
	if (m_direction == Down) {
		return;
	}
	m_direction = Down;
	start(duration * m_value);
}

void ToggleAnimation::start(int duration) {
	
	stop();

        m_step = 1/(qreal)(duration);
	m_finished  = false;
	m_value -= m_step; 
	m_oldValue  = m_value;
	
	if (duration <= 0) {
		m_value     = m_direction == Up ? 1.0 : 0.0;
		animate(m_value);
		m_finished  = true;

		emit finished();
	}
	else {
		m_scrollAnimation.setDuration(duration);
                m_scrollAnimation.start();
	}
}

void ToggleAnimation::animate(qreal value)
{

  if(m_direction == Up) 
  animateUp(value);
  else 
    animateDown(value);
}

void ToggleAnimation::animateUp(qreal progress) {
	m_value =  m_step * progress;
	emit update();
}

void ToggleAnimation::animateDown(qreal progress) {
	m_value = 1 - m_step * progress;
	emit update();
}

void ToggleAnimation::sfinished() {
	
		m_value     = m_direction == Up ? 1.0 : 0.0;
		m_finished  = true;

		emit finished();
}

} // namespace SmoothTasks
