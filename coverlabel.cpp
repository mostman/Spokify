/*
 * This file is part of Spokify.
 * Copyright (C) 2010 Rafael Fernández López <ereslibre@kde.org>
 *
 * Spokify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Spokify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Spokify.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "coverlabel.h"

#include <QtGui/QMovie>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <KIconEffect>

CoverLabel::CoverLabel(QWidget *parent)
    : QLabel(parent)
    , m_hovered(false)
{
    setCursor(Qt::PointingHandCursor);
    setMinimumSize(QSize(100, 100));
}

CoverLabel::~CoverLabel()
{
}

void CoverLabel::paintEvent(QPaintEvent *event)
{
    QPixmap labelPixmap;

    if (movie()) {
        labelPixmap = movie()->currentPixmap();
    } else {
        labelPixmap = *pixmap();
    }

    int pSize = qMin(event->rect().size().width(), event->rect().size().height());
    const QSize pixmapSize(pSize, pSize);

    int x = (size() - pixmapSize).width() / 2;
    int y = (size() - pixmapSize).height() / 2;

    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(x, y, pSize, pSize, labelPixmap);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);
    p.save();
    if (isEnabled() && (!movie() && m_hovered)) {
        p.setOpacity(0.5);
        p.fillRect(QRect(x, y, pSize, pSize), palette().highlight());
    } else if (!isEnabled()) {
        p.setOpacity(0.5);
        p.fillRect(QRect(x, y, pSize, pSize), palette().window());
    }
    p.restore();
}

void CoverLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit coverClicked();
    QLabel::mouseReleaseEvent(event);
}

void CoverLabel::enterEvent(QEvent *event)
{
    m_hovered = true;
    QLabel::enterEvent(event);
    update();
}

void CoverLabel::leaveEvent(QEvent *event)
{
    m_hovered = false;
    QLabel::leaveEvent(event);
    update();
}
