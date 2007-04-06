/*****************************************************************************
 * Help.cpp : Help and About dialogs
 ****************************************************************************
 * Copyright (C) 2006 the VideoLAN team
 * $Id: Messages.cpp 16024 2006-07-13 13:51:05Z xtophe $
 *
 * Authors: Jean-Baptiste Kempf <jb (at) videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "dialogs/help.hpp"

#include "dialogs_provider.hpp"
#include "util/qvlcframe.hpp"
#include "qt4.hpp"

#include <QTextBrowser>
#include <QTabWidget>
#include <QFile>
#include <QLabel>

HelpDialog *HelpDialog::instance = NULL;

HelpDialog::HelpDialog( intf_thread_t *_p_intf) :  QVLCFrame( _p_intf )
{
    setWindowTitle( qtr( "Help" ) );
    resize( 600, 500 );

    QGridLayout *layout = new QGridLayout( this );
    QTextBrowser *helpBrowser = new QTextBrowser( this );
    QPushButton *closeButton = new QPushButton( qtr( "&Close" ) );
    closeButton->setDefault( true );

    layout->addWidget( helpBrowser, 0, 0, 1, 0 );
    layout->addWidget( closeButton, 1, 3 );

    BUTTONACT( closeButton, close() );
}

HelpDialog::~HelpDialog()
{
}
void HelpDialog::close()
{
    this->toggleVisible();
}

AboutDialog *AboutDialog::instance = NULL;

AboutDialog::AboutDialog( intf_thread_t *_p_intf) :  QVLCFrame( _p_intf )
{
    setWindowTitle( qtr( "About" ) );
    resize( 600, 500 );

    QGridLayout *layout = new QGridLayout( this );
    QTabWidget *tab = new QTabWidget( this );

    QPushButton *closeButton = new QPushButton( qtr( "&Close" ) );
    closeButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    closeButton->setDefault( true );

    QLabel *introduction = new QLabel( qtr( "Infos about VLC media player" ) );

    layout->addWidget( introduction, 0, 0, 1, 2 );
    layout->addWidget( tab, 1, 0, 1, 2 );
    layout->addWidget( closeButton, 2, 1, 1, 1 );

    /* GPL License */
    QFile *licenseFile = new QFile( "/usr/src/vlc/COPYING" );
    QTextEdit *licenseEdit = new QTextEdit( this );
    licenseEdit->setText( licenseFile->readAll() );
    licenseEdit->setReadOnly( true );

    /* People who helped */
    QFile *thanksFile = new QFile( "/usr/src/vlc/THANKS" );
    QTextEdit *thanksEdit = new QTextEdit( this );
    thanksEdit->setText( thanksFile->readAll() );
    thanksEdit->setReadOnly( true );

    /* add the tabs to the Tabwidget */
    tab->addTab( NULL, _( "Information" ) );
    tab->addTab( NULL, _( "Authors" ) );
    tab->addTab( thanksEdit, _("Thanks") );
    tab->addTab( licenseEdit, _("Distribution License") );

    BUTTONACT( closeButton, close() );
}

AboutDialog::~AboutDialog()
{
}
void AboutDialog::close()
{
    this->toggleVisible();
}
