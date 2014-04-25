/***********************************************************************************
* Smooth Tasks
* Copyright (C) 2012 Sébastien Lambert <opensc@beonis.fr>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
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

#ifndef _ANIMATE_H_
#define _ANIMATE_H_

#include <QAbstractAnimation>

namespace SmoothTasks {

template <class T> class Animate : public QAbstractAnimation
	{
	  //Q_OBJECT
	  public :
	    Animate(T& owner): m_owner(owner),m_duration(0) {};
            virtual ~Animate(){}
	    int duration() const { return m_duration;}
	    void setDuration(int duration){ m_duration = duration; }
	  protected :
	    void updateCurrentTime(int currentTime)
	      {
		m_owner.animate(currentTime);
	      }

	  private :
	    T& m_owner;
            int m_duration;
	};
	
#define QAnimate(T,TFinal) class T; class TFinal: public Animate<T> { Q_OBJECT public: TFinal(T& src):Animate(src){} };
}	
#endif //_ANIMATE_H_