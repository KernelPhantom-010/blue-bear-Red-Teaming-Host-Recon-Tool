#pragma once

#include <QObject>
#include <QTabWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>

// Fadet die jeweils neu angezeigte Tab-Seite beim Wechsel sanft ein.
class TabFadeAnimation : public QObject
{
	Q_OBJECT
public:
	explicit TabFadeAnimation(QTabWidget* tabWidget, QObject* parent = nullptr)
		: QObject(parent), m_tabWidget(tabWidget)
	{
		connect(m_tabWidget, &QTabWidget::currentChanged, this, &TabFadeAnimation::animate);
	}

private slots:
	void animate(int index)
	{
		QWidget* page = m_tabWidget->widget(index);
		if (!page)
			return;

		auto* effect = new QGraphicsOpacityEffect(page);
		effect->setOpacity(0.0);
		page->setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(320);
		animation->setStartValue(0.0);
		animation->setEndValue(1.0);
		animation->setEasingCurve(QEasingCurve::OutQuint);

		connect(animation, &QPropertyAnimation::finished, page, [page]() {
			page->setGraphicsEffect(nullptr);
		});

		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

private:
	QTabWidget* m_tabWidget;
};
