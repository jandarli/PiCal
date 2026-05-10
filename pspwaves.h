#ifndef PSPWAVES_H
#define PSPWAVES_H

#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <cmath>

inline void drawPSPWaves(QPainter *painter, const QRect &clipRect, const QRect &canvasRect, double phase)
{
    painter->fillRect(clipRect, QColor(0x8B, 0x00, 0x00));
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipRect(clipRect);

    const double W = canvasRect.width();
    const double H = canvasRect.height();

    struct Band { double yFrac, ampFrac, freq; int alpha; };
    const Band bands[] = {
        {0.18, 0.09, 1.0, 65},
        {0.46, 0.11, 0.7, 70},
        {0.74, 0.09, 1.2, 60},
    };

    for (const auto &b : bands) {
        const double cy  = canvasRect.top() + b.yFrac * H;
        const double amp = b.ampFrac * H;
        const double bw  = H * 0.02;

        QPainterPath path;
        for (int x = 0; x <= static_cast<int>(W); ++x) {
            double y = cy + amp * std::sin(2.0 * M_PI * b.freq * x / W - phase);
            if (x == 0) {
                path.moveTo(canvasRect.left() + x, y);
            } else {
                path.lineTo(canvasRect.left() + x, y);
            }
        }

        for (int x = static_cast<int>(W); x >= 0; --x) {
            double y = cy + amp * std::sin(2.0 * M_PI * b.freq * x / W - phase) + bw;
            path.lineTo(canvasRect.left() + x, y);
        }

        path.closeSubpath();

        // Fade the band in/out vertically so edges are soft rather than hard-cut
        QLinearGradient grad(0, cy - amp, 0, cy + amp + bw);
        
        grad.setColorAt(0.0, QColor(230, 110, 110, 0));
        grad.setColorAt(0.3, QColor(230, 110, 110, b.alpha));
        grad.setColorAt(0.7, QColor(230, 110, 110, b.alpha));
        grad.setColorAt(1.0, QColor(230, 110, 110, 0));

        painter->fillPath(path, grad);
    }

    painter->restore();
}

#endif
