// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define BT_POINTER_GUARD(pointers) if(!ensure(pointers)) { return; }