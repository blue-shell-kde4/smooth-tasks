


#include "SmoothTasks/TaskStateAnimation.h"

#include <Plasma/Animator>

namespace SmoothTasks {

TaskStateAnimation::TaskStateAnimation()
	: QObject(),
	  m_scrollAnimation(*this),
	  m_fromState(Normal),
	  m_toState(Normal),
	  m_hover(0.0),
	  m_minimized(0.0),
	  m_attention(0.0),
	  m_focus(0.0),
	  m_lastProgress(0.0) {
	connect(
		&m_scrollAnimation, SIGNAL(finished()),
		this, SLOT(animationFinished()));
}

void TaskStateAnimation::stop() {
	m_scrollAnimation.stop();
}

void TaskStateAnimation::start( int duration) {
	m_step = 1/duration;
	m_lastProgress = 0.0;

	if (duration <= 0) {
		animate(1.0);
		animationFinished();
	}
	else {
		m_scrollAnimation.setDuration(duration);
                m_scrollAnimation.start();
	}
}

void TaskStateAnimation::setState(int newState, int duration) {
	if (m_toState == newState) {
		return;
	}

	// from  to newTo newFrom
	//   0    0    0    0     
	//   0    0    1    0     
	//   0    1    0    1     (m_fromState ^ m_toState) & ~newState
	//   0    1    1    0     (m_fromState ^ m_toState) & ~newState
	//   1    0    0    1     (m_fromState ^ m_toState) & ~newState
	//   1    0    1    0     (m_fromState ^ m_toState) & ~newState
	//   1    1    0    1     (m_fromState & m_toState)
	//   1    1    1    1     (m_fromState & m_toState)

	stop();
	m_fromState = ((m_fromState ^ m_toState) & ~newState) | (m_fromState & m_toState);
	m_toState   = newState;
	start(duration);
}

void TaskStateAnimation::animate(qreal progress) {
	qreal delta = progress - m_lastProgress;
	m_lastProgress = progress;
	int animatedState = m_fromState ^ m_toState;

	if (animatedState & Hover) {
		if (m_toState & Hover) {
			m_hover += delta;
			if (m_hover >= 1.0) {
				m_hover = 1.0;
				m_fromState |= Hover;
			}
		}
		else {
			m_hover -= delta;
			if (m_hover <= 0.0) {
				m_hover = 0.0;
				m_fromState &= ~Hover;
			}
		}
	}
	
	if (animatedState & Minimized) {
		if (m_toState & Minimized) {
			m_minimized += delta;
			if (m_minimized >= 1.0) {
				m_minimized = 1.0;
				m_fromState |= Minimized;
			}
		}
		else {
			m_minimized -= delta;
			if (m_minimized <= 0.0) {
				m_minimized = 0.0;
				m_fromState &= ~Minimized;
			}
		}
	}
	
	if (animatedState & Attention) {
		if (m_toState & Attention) {
			m_attention += delta;
			if (m_attention >= 1.0) {
				m_attention = 1.0;
				m_fromState |= Attention;
			}
		}
		else {
			m_attention -= delta;
			if (m_attention <= 0.0) {
				m_attention = 0.0;
				m_fromState &= ~Attention;
			}
		}
	}
	
	if (animatedState & Focus) {
		if (m_toState & Focus) {
			m_focus += delta;
			if (m_focus >= 1.0) {
				m_focus = 1.0;
				m_fromState |= Focus;
			}
		}
		else {
			m_focus -= delta;
			if (m_focus <= 0.0) {
				m_focus = 0.0;
				m_fromState &= ~Focus;
			}
		}
	}

	emit update();
}

void TaskStateAnimation::animationFinished() {
		m_fromState = m_toState;
		m_hover     = m_toState & Hover     ? 1.0 : 0.0;
		m_minimized = m_toState & Minimized ? 1.0 : 0.0;
		m_attention = m_toState & Attention ? 1.0 : 0.0;
		m_focus     = m_toState & Focus     ? 1.0 : 0.0;
}

} // namespace SmoothTasks
