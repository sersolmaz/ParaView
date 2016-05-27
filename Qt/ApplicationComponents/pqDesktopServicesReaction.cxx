/*=========================================================================

   Program: ParaView
   Module:  pqDesktopServicesReaction.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "pqDesktopServicesReaction.h"

#include "pqCoreUtilities.h"

#include <QDesktopServices>
#include <QFileInfo>
#include <QMessageBox>
#include <QtDebug>

#include <iostream>
//-----------------------------------------------------------------------------
pqDesktopServicesReaction::pqDesktopServicesReaction(
  const QUrl& url, QAction* parentObject)
  : Superclass(parentObject),
  URL(url)
{
}

//-----------------------------------------------------------------------------
pqDesktopServicesReaction::~pqDesktopServicesReaction()
{
}

//-----------------------------------------------------------------------------
void pqDesktopServicesReaction::openUrl(const QUrl& url)
{
  if (url.isLocalFile() && !QFileInfo(url.toLocalFile()).exists())
    {
    QString filename = QFileInfo(url.toLocalFile()).absoluteFilePath();
    QString msg = QString("The requested file is not available in your installation. "
      "You can manually obtain and place the file (or ask your administrators) at the "
      "following location for this to work.\n\n'%1'").arg(filename);
    // dump to cout for easy copy/paste.
    std::cout << msg.toUtf8().data() << std::endl;
    QMessageBox::warning(pqCoreUtilities::mainWidget(), "Missing file", msg, QMessageBox::Ok);
    }
  else if (!QDesktopServices::openUrl(url))
    {
    qCritical() << "Failed to open '" << url << "'";
    }
}
