/***********************************************************************************
* Smooth Tasks
* Copyright (C) 2009 Marcin Baszczewski <marcin.baszczewski@gmail.com>
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
#ifndef SMOOTHTASKSLIGHT_H
#define SMOOTHTASKSLIGHT_H

// Qt
#include <QObject>
#include <QPixmap>
#include <QIcon>
#include <QAbstractAnimation>
#include <QEasingCurve>

class QRadialGradient;
class QTimer;
class QStyleOptionGraphicsItem;

namespace SmoothTasks {

class TaskItem;

class Light : public QAbstractAnimation {
	Q_OBJECT

public:
	enum AnimationType {
		NoAnimation,
		StartupAnimation,
		AttentionAnimation
	};

	Light(TaskItem *item);
	~Light();

	int duration() const;
	void paint(QPainter *p, const QRectF& geometry, const QPointF& mousePos, bool mouseIn, const bool isRotated);

public slots:
	void startAnimation(AnimationType animation, int duration = 300);
	void stopAnimation();

protected : 
	void updateCurrentTime(int currentTime) ;
private:
  
	QEasingCurve m_curve;
	TaskItem     *m_item;
	int           m_currentAnimationDuration;
	qreal         m_progress;
	bool          m_move;
	AnimationType m_currentAnimation;
	bool          m_repeater;
	qreal	      m_step;

signals:
	void update();
};

} // namespace SmoothTasks
#endif
