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
#ifndef SMOOTHTASKS_TOGGLEANIMATION_H
#define SMOOTHTASKS_TOGGLEANIMATION_H

#include <QObject>
#include <QEasingCurve>

#include "Animate.h"


namespace SmoothTasks {
  
//QAnimate(ToggleAnimation,ToggleAnimationAnim)
class ToggleAnimation;

class ToggleAnimationAnim: public Animate<ToggleAnimation> 
{ 
  Q_OBJECT 
 public:ToggleAnimationAnim(ToggleAnimation& src):Animate(src){} 
};

class ToggleAnimation : public QObject {
	Q_OBJECT
	
	friend  class Animate<ToggleAnimation>;

public:
	enum Direction {
		Up,
		Down
	};

	ToggleAnimation(QObject *parent)
		: QObject(parent),
		m_scrollAnimation(*this),
		  m_value(0.0),
		  m_oldValue(0.0),
		  m_direction(Down),
		  m_finished(false) { init(); }

	ToggleAnimation()
		: QObject(),
		m_scrollAnimation(*this),
		  m_value(0.0),
		  m_oldValue(0.0),
		  m_direction(Down),
		  m_finished(false) { init(); }

	~ToggleAnimation() { stop(); }

	void      start(Direction direction, int duration);
	void      startUp(int duration);
	void      startDown(int duration);
	void      stop();
	qreal     value()      const { return m_value; }
	bool      isActive()   const { return m_scrollAnimation.state() == QAbstractAnimation::Running; }
	bool      isFinished() const { return m_finished; }
	bool      atTop()      const { return m_finished && m_direction == Up; }
	bool      atBottom()   const { return m_finished && m_direction == Down; }
	Direction direction()  const { return m_direction; }

	void animate(qreal value);
signals:
	void update();
	void finished();

private slots:
	void animateUp(qreal progress);
	void animateDown(qreal progress);
	void sfinished();

private:
	void init();
	void start(int duration);

        ToggleAnimationAnim   m_scrollAnimation;
        QEasingCurve m_curve;
        qreal     m_step;
	qreal     m_value;
	qreal     m_oldValue;
	Direction m_direction;
	bool      m_finished;
};

} // namespace SmoothTasks

#endif
