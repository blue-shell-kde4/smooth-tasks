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
#ifndef SMOOTHTASKS_TASKSTATEANIMATION_H
#define SMOOTHTASKS_TASKSTATEANIMATION_H

#include <QObject>
#include <QEasingCurve>

#include "Animate.h"

namespace SmoothTasks {
  
// QAnimate(TaskStateAnimation,TaskStateAnimationAnim)
 
 class TaskStateAnimation;

class TaskStateAnimationAnim: public Animate<TaskStateAnimation> 
{ 
  Q_OBJECT 
 public:TaskStateAnimationAnim(TaskStateAnimation& src):Animate(src){} 
};

class TaskStateAnimation : public QObject {
	Q_OBJECT
	
	friend  class Animate<TaskStateAnimation>;

public:
	TaskStateAnimation();

	enum StateFlag {
		Normal    = 0,
		Hover     = 1,
		Minimized = 2,
		Attention = 4,
		Focus     = 8,
		Launcher  = 16
	};

	// animation progresses:
	qreal hover()     const { return m_hover; }
	qreal minimized() const { return m_minimized; }
	qreal attention() const { return m_attention; }
	qreal focus()     const { return m_focus; }

	int fromState()         const { return m_fromState; }
	int toState()           const { return m_toState; }
	int animatedState()     const { return m_fromState ^ m_toState; }
	int animatedToState()   const { return (m_fromState ^ m_toState) & m_toState; }
	int animatedFromState() const { return (m_fromState ^ m_toState) & m_fromState; }
	int reachedUpState()    const { return m_fromState & m_toState; }
	int reachedDownState()  const { return ~m_fromState & ~m_toState; }
	int reachedState()      const { return ~(m_fromState ^ m_toState); }
	int shownState()        const { return m_fromState | m_toState; }
	int hiddenState()       const { return ~(m_fromState | m_toState); }

	bool isActive() const { return m_scrollAnimation.state() == QAbstractAnimation::Running; }

public slots:
	void setState(int state, int duration);

private slots:
	void animate(qreal progress);
	void animationFinished();

private:
	void stop();
	void start(int duration);

signals:
	void update();

private:
	TaskStateAnimationAnim   m_scrollAnimation;
        QEasingCurve m_curve;
        qreal     m_step;

	int m_fromState;
	int m_toState;

	qreal m_hover;
	qreal m_minimized;
	qreal m_attention;
	qreal m_focus;

	qreal m_lastProgress;
};

} // namespace SmoothTasks 
#endif
