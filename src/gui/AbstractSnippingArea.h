/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_ABSTRACTSNIPPINGAREA_H
#define KSNIP_ABSTRACTSNIPPINGAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

#include "src/widgets/CursorFactory.h"
#include "src/common/helper/MathHelper.h"
#include "src/backend/KsnipConfig.h"

class AbstractSnippingArea : public QWidget
{
    Q_OBJECT
public:
	explicit AbstractSnippingArea();
    ~AbstractSnippingArea() override;
    void showWithoutBackground();
    void showWithBackground(const QPixmap& background);
    virtual QRect selectedRectArea() const = 0;
    bool closeSnippingArea();

signals:
    void finished();
    void canceled();

protected:
    QRect mCaptureArea;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    virtual void setFullScreen() = 0;
	virtual QPoint getMousePosition() const = 0;

private:
    QPoint         mMouseDownPosition;
    bool           mMouseIsDown;
    bool           mCursorRulerEnabled;
    bool           mCursorInfoEnabled;
    CursorFactory *mCursorFactory;
    KsnipConfig   *mConfig;
    QPixmap       *mBackground;

    void setBackgroundImage(const QPixmap &background);
    void clearBackgroundImage();
    void init();
	void updateCapturedArea(const QPoint &point1, const QPoint &point2);
    QString createPositionInfoText(int number1, int number2) const;
    void drawCursorRuler(QPainter &painter) const;
    void drawCursorPositionInfo(QPainter &painter) const;
    void drawCursorSizeInfo(QPainter &painter) const;
    void drawCursorWidthInfo(QPainter &painter) const;
    void drawCursorHeightInfo(QPainter &painter) const;
    QRect getTextBounding(const QPainter &painter, const QString &text) const;
    virtual void showSnippingArea();
};

#endif // KSNIP_ABSTRACTSNIPPINGAREA_H
