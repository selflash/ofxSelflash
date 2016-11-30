#pragma once

#define USE_FLASH_OBJECT

#include "STween2D.h"
typedef fltw::STween2D flSTween2D;

#include "STweener.h"
#include "CallBackFuncion.h"
#include "DelayedCallFunction.h"
#include "STweenSelector.h"
#include "STweenCore.h"
#include "STween.h"

typedef fltw::STweener flTweener;
typedef fltw::CallBackFuncion<float> flCallBackFuncion;
typedef fltw::DelayedCallFunction<float> flDelayedCallFunction;
typedef fltw::STweenSelector flSTweenSelector;
typedef fltw::STweenCore flSTweenCore;
typedef fltw::STween flSTween;