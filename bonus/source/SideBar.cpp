/*
 * =====================================================================================
 *
 *       Filename:  SideBar.cpp
 *
 *    Description:  
 *
 *        Created:  27/03/2016 15:21:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QFormLayout>

#include "MainWindow.hpp"
#include "MediaPlayer.hpp"
#include "PlayerWidget.hpp"
#include "SideBar.hpp"

SideBar::SideBar(MediaPlayer *mediaPlayer, QWidget *parent) : QWidget(parent) {
	m_mediaPlayer = mediaPlayer;
	
	setMinimumSize(MainWindow::width / 5, 0);
	
	m_layout = new QVBoxLayout(this);
	
	initMusicPlayerWidgets();
	initYoutubeWidgets();
	initPlayerWidgets();
	
	m_layout->addStretch();
	
	connect(m_youtubeVideoButton, SIGNAL(pressed()), this, SLOT(downloadYoutubeMusic()));
	connect(m_mediaPlayer, SIGNAL(downloadFinished()), this, SLOT(downloadFinished()));
	connect(m_mediaPlayer, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64)));
}

void SideBar::initMusicPlayerWidgets() {
	QGroupBox *musicBox = new QGroupBox("Now playing", this);
	QHBoxLayout *layout = new QHBoxLayout(musicBox);
	
	QLabel *youtubeVideoNameLabel = new QLabel("", musicBox);
	youtubeVideoNameLabel->setWordWrap(true);
	
	layout->addWidget(youtubeVideoNameLabel);
	m_layout->addWidget(musicBox);
	
	connect(m_mediaPlayer, SIGNAL(musicChanged(const QString &)), youtubeVideoNameLabel, SLOT(setText(const QString &)));
}

void SideBar::initYoutubeWidgets() {
	QGroupBox *youtubeBox = new QGroupBox("Youtube", this);
	m_youtubeVideoIDWidget = new QLineEdit(youtubeBox);
	m_youtubeVideoButton = new QPushButton("Download and play", youtubeBox);
	
	m_downloadProgressBar = new QProgressBar(youtubeBox);
	m_downloadProgressBar->setRange(0, 100);
	m_downloadProgressBar->setVisible(false);
	
	QFormLayout *layout = new QFormLayout(youtubeBox);
	layout->addRow("http://youtube.com/watch?v=", m_youtubeVideoIDWidget);
	layout->addRow(m_downloadProgressBar);
	layout->addRow(m_youtubeVideoButton);
	
	m_layout->addWidget(youtubeBox);
}

void SideBar::initPlayerWidgets() {
	for (int i = 0 ; i < 4 ; i++) {
		m_playerWidgets[i] = new PlayerWidget(i + 1, this);
		m_layout->addWidget(m_playerWidgets[i]);
	}
}

void SideBar::downloadProgress(qint64 read, qint64 total) {
	m_downloadProgressBar->setVisible(true);
	m_downloadProgressBar->setValue(read * 100 / total);
}

void SideBar::downloadYoutubeMusic() {
	m_mediaPlayer->playYoutubeURL(m_youtubeVideoIDWidget->text());
	
	m_youtubeVideoButton->setEnabled(false);
	m_youtubeVideoIDWidget->setEnabled(false);
}

void SideBar::downloadFinished() {
	m_youtubeVideoButton->setEnabled(true);
	m_youtubeVideoIDWidget->setEnabled(true);
	m_youtubeVideoIDWidget->setText("");
	m_downloadProgressBar->reset();
	m_downloadProgressBar->setVisible(false);
}

