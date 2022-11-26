QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../muparserx-master/parser/mpError.cpp \
    ../muparserx-master/parser/mpFuncCmplx.cpp \
    ../muparserx-master/parser/mpFuncCommon.cpp \
    ../muparserx-master/parser/mpFuncMatrix.cpp \
    ../muparserx-master/parser/mpFuncNonCmplx.cpp \
    ../muparserx-master/parser/mpFuncStr.cpp \
    ../muparserx-master/parser/mpICallback.cpp \
    ../muparserx-master/parser/mpIOprt.cpp \
    ../muparserx-master/parser/mpIOprtBinShortcut.cpp \
    ../muparserx-master/parser/mpIPackage.cpp \
    ../muparserx-master/parser/mpIToken.cpp \
    ../muparserx-master/parser/mpIValReader.cpp \
    ../muparserx-master/parser/mpIValue.cpp \
    ../muparserx-master/parser/mpIfThenElse.cpp \
    ../muparserx-master/parser/mpOprtBinAssign.cpp \
    ../muparserx-master/parser/mpOprtBinCommon.cpp \
    ../muparserx-master/parser/mpOprtBinShortcut.cpp \
    ../muparserx-master/parser/mpOprtCmplx.cpp \
    ../muparserx-master/parser/mpOprtIndex.cpp \
    ../muparserx-master/parser/mpOprtMatrix.cpp \
    ../muparserx-master/parser/mpOprtNonCmplx.cpp \
    ../muparserx-master/parser/mpOprtPostfixCommon.cpp \
    ../muparserx-master/parser/mpPackageCmplx.cpp \
    ../muparserx-master/parser/mpPackageCommon.cpp \
    ../muparserx-master/parser/mpPackageMatrix.cpp \
    ../muparserx-master/parser/mpPackageNonCmplx.cpp \
    ../muparserx-master/parser/mpPackageStr.cpp \
    ../muparserx-master/parser/mpPackageUnit.cpp \
    ../muparserx-master/parser/mpParser.cpp \
    ../muparserx-master/parser/mpParserBase.cpp \
    ../muparserx-master/parser/mpParserMessageProvider.cpp \
    ../muparserx-master/parser/mpRPN.cpp \
    ../muparserx-master/parser/mpScriptTokens.cpp \
    ../muparserx-master/parser/mpTest.cpp \
    ../muparserx-master/parser/mpTokenReader.cpp \
    ../muparserx-master/parser/mpValReader.cpp \
    ../muparserx-master/parser/mpValue.cpp \
    ../muparserx-master/parser/mpValueCache.cpp \
    ../muparserx-master/parser/mpVariable.cpp \
    muparserx.cpp

HEADERS += \
    ../muparserx-master/parser/mpCompat.h \
    ../muparserx-master/parser/mpDefines.h \
    ../muparserx-master/parser/mpError.h \
    ../muparserx-master/parser/mpFuncCmplx.h \
    ../muparserx-master/parser/mpFuncCommon.h \
    ../muparserx-master/parser/mpFuncMatrix.h \
    ../muparserx-master/parser/mpFuncNonCmplx.h \
    ../muparserx-master/parser/mpFuncStr.h \
    ../muparserx-master/parser/mpFwdDecl.h \
    ../muparserx-master/parser/mpICallback.h \
    ../muparserx-master/parser/mpIOprt.h \
    ../muparserx-master/parser/mpIOprtBinShortcut.h \
    ../muparserx-master/parser/mpIPackage.h \
    ../muparserx-master/parser/mpIPrecedence.h \
    ../muparserx-master/parser/mpIToken.h \
    ../muparserx-master/parser/mpIValReader.h \
    ../muparserx-master/parser/mpIValue.h \
    ../muparserx-master/parser/mpIfThenElse.h \
    ../muparserx-master/parser/mpMatrix.h \
    ../muparserx-master/parser/mpMatrixError.h \
    ../muparserx-master/parser/mpOprtBinAssign.h \
    ../muparserx-master/parser/mpOprtBinCommon.h \
    ../muparserx-master/parser/mpOprtBinShortcut.h \
    ../muparserx-master/parser/mpOprtCmplx.h \
    ../muparserx-master/parser/mpOprtIndex.h \
    ../muparserx-master/parser/mpOprtMatrix.h \
    ../muparserx-master/parser/mpOprtNonCmplx.h \
    ../muparserx-master/parser/mpOprtPostfixCommon.h \
    ../muparserx-master/parser/mpPackageCmplx.h \
    ../muparserx-master/parser/mpPackageCommon.h \
    ../muparserx-master/parser/mpPackageMatrix.h \
    ../muparserx-master/parser/mpPackageNonCmplx.h \
    ../muparserx-master/parser/mpPackageStr.h \
    ../muparserx-master/parser/mpPackageUnit.h \
    ../muparserx-master/parser/mpParser.h \
    ../muparserx-master/parser/mpParserBase.h \
    ../muparserx-master/parser/mpParserMessageProvider.h \
    ../muparserx-master/parser/mpRPN.h \
    ../muparserx-master/parser/mpScriptTokens.h \
    ../muparserx-master/parser/mpStack.h \
    ../muparserx-master/parser/mpTest.h \
    ../muparserx-master/parser/mpTokenReader.h \
    ../muparserx-master/parser/mpTypes.h \
    ../muparserx-master/parser/mpValReader.h \
    ../muparserx-master/parser/mpValue.h \
    ../muparserx-master/parser/mpValueCache.h \
    ../muparserx-master/parser/mpVariable.h \
    ../muparserx-master/parser/suSortPred.h \
    ../muparserx-master/parser/suStringTokens.h \
    ../muparserx-master/parser/utGeneric.h \
    muparserx.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
