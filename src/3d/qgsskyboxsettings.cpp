/***************************************************************************
  qgsskyboxsettings.cpp
  --------------------------------------
  Date                 : August 2020
  Copyright            : (C) 2020 by Belgacem Nedjima
  Email                : gb uderscore nedjima at esi dot dz
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsskyboxsettings.h"

#include <QDomDocument>

#include "qgsreadwritecontext.h"
#include "qgssymbollayerutils.h"

void QgsSkyboxSettings::readXml( const QDomElement &element, const QgsReadWriteContext &context )
{
  const QgsPathResolver &pathResolver = context.pathResolver();
  mIsSkyboxEnabled = element.attribute( QStringLiteral( "skybox-enabled" ) ).toInt();
  QString skyboxTypeStr = element.attribute( QStringLiteral( "skybox-type" ) );
  if ( skyboxTypeStr == QStringLiteral( "Distinct Faces" ) )
    mSkyboxType = QgsSkyboxEntity::DistinctTexturesSkybox;
  else if ( skyboxTypeStr == QStringLiteral( "Panoramic texture" ) )
    mSkyboxType = QgsSkyboxEntity::PanoramicSkybox;
  mPanoramicTexturePath = pathResolver.readPath( element.attribute( QStringLiteral( "panoramic-texture-path" ) ) );
  mCubeMapFacesPaths.clear();
  mCubeMapFacesPaths[ QStringLiteral( "posX" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "posX-texture-path" ) ) );
  mCubeMapFacesPaths[ QStringLiteral( "posY" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "posY-texture-path" ) ) );
  mCubeMapFacesPaths[ QStringLiteral( "posZ" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "posZ-texture-path" ) ) );
  mCubeMapFacesPaths[ QStringLiteral( "negX" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "negX-texture-path" ) ) );
  mCubeMapFacesPaths[ QStringLiteral( "negY" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "negY-texture-path" ) ) );
  mCubeMapFacesPaths[ QStringLiteral( "negZ" ) ] = pathResolver.readPath( element.attribute( QStringLiteral( "negZ-texture-path" ) ) );
}

void QgsSkyboxSettings::writeXml( QDomElement &element, const QgsReadWriteContext &context ) const
{
  element.setAttribute( QStringLiteral( "skybox-enabled" ), mIsSkyboxEnabled );
  switch ( mSkyboxType )
  {
    case QgsSkyboxEntity::DistinctTexturesSkybox:
      element.setAttribute( QStringLiteral( "skybox-type" ), QStringLiteral( "Distinct Faces" ) );
      break;
    case QgsSkyboxEntity::PanoramicSkybox:
      element.setAttribute( QStringLiteral( "skybox-type" ), QStringLiteral( "Panoramic texture" ) );
      break;
  }

  const QgsPathResolver &pathResolver = context.pathResolver();
  element.setAttribute( QStringLiteral( "panoramic-texture-path" ), pathResolver.writePath( mPanoramicTexturePath ) );
  element.setAttribute( QStringLiteral( "posX-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "posX" ) ] ) );
  element.setAttribute( QStringLiteral( "posY-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "posY" ) ] ) );
  element.setAttribute( QStringLiteral( "posZ-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "posZ" ) ] ) );
  element.setAttribute( QStringLiteral( "negX-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "negX" ) ] ) );
  element.setAttribute( QStringLiteral( "negY-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "negY" ) ] ) );
  element.setAttribute( QStringLiteral( "negZ-texture-path" ), pathResolver.writePath( mCubeMapFacesPaths[ QStringLiteral( "negZ" ) ] ) );
}
