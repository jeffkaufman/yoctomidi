/*********************************************************************
 *
 * $Id: yocto_accelerometer.h 31436 2018-08-07 15:28:18Z seb $
 *
 * Declares yFindAccelerometer(), the high-level API for Accelerometer functions
 *
 * - - - - - - - - - License information: - - - - - - - - -
 *
 *  Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 *  Yoctopuce Sarl (hereafter Licensor) grants to you a perpetual
 *  non-exclusive license to use, modify, copy and integrate this
 *  file into your software for the sole purpose of interfacing
 *  with Yoctopuce products.
 *
 *  You may reproduce and distribute copies of this file in
 *  source or object form, as long as the sole purpose of this
 *  code is to interface with Yoctopuce products. You must retain
 *  this notice in the distributed source file.
 *
 *  You should refer to Yoctopuce General Terms and Conditions
 *  for additional information regarding your rights and
 *  obligations.
 *
 *  THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *  WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *  EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *  INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 *  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR
 *  SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
 *  LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *  CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *  BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *  WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#include "yocto_api.h"
CF_EXTERN_C_BEGIN

@class YAccelerometer;

//--- (YAccelerometer globals)
typedef void (*YAccelerometerValueCallback)(YAccelerometer *func, NSString *functionValue);
typedef void (*YAccelerometerTimedReportCallback)(YAccelerometer *func, YMeasure *measure);
#ifndef _Y_GRAVITYCANCELLATION_ENUM
#define _Y_GRAVITYCANCELLATION_ENUM
typedef enum {
    Y_GRAVITYCANCELLATION_OFF = 0,
    Y_GRAVITYCANCELLATION_ON = 1,
    Y_GRAVITYCANCELLATION_INVALID = -1,
} Y_GRAVITYCANCELLATION_enum;
#endif
#define Y_BANDWIDTH_INVALID             YAPI_INVALID_INT
#define Y_XVALUE_INVALID                YAPI_INVALID_DOUBLE
#define Y_YVALUE_INVALID                YAPI_INVALID_DOUBLE
#define Y_ZVALUE_INVALID                YAPI_INVALID_DOUBLE
//--- (end of YAccelerometer globals)

//--- (YAccelerometer class start)
/**
 * YAccelerometer Class: Accelerometer function interface
 *
 * The YSensor class is the parent class for all Yoctopuce sensors. It can be
 * used to read the current value and unit of any sensor, read the min/max
 * value, configure autonomous recording frequency and access recorded data.
 * It also provide a function to register a callback invoked each time the
 * observed value changes, or at a predefined interval. Using this class rather
 * than a specific subclass makes it possible to create generic applications
 * that work with any Yoctopuce sensor, even those that do not yet exist.
 * Note: The YAnButton class is the only analog input which does not inherit
 * from YSensor.
 */
@interface YAccelerometer : YSensor
//--- (end of YAccelerometer class start)
{
@protected
//--- (YAccelerometer attributes declaration)
    int             _bandwidth;
    double          _xValue;
    double          _yValue;
    double          _zValue;
    Y_GRAVITYCANCELLATION_enum _gravityCancellation;
    YAccelerometerValueCallback _valueCallbackAccelerometer;
    YAccelerometerTimedReportCallback _timedReportCallbackAccelerometer;
//--- (end of YAccelerometer attributes declaration)
}
// Constructor is protected, use yFindAccelerometer factory function to instantiate
-(id)    initWith:(NSString*) func;

//--- (YAccelerometer private methods declaration)
// Function-specific method for parsing of JSON output and caching result
-(int)             _parseAttr:(yJsonStateMachine*) j;

//--- (end of YAccelerometer private methods declaration)
//--- (YAccelerometer yapiwrapper declaration)
//--- (end of YAccelerometer yapiwrapper declaration)
//--- (YAccelerometer public methods declaration)
/**
 * Returns the measure update frequency, measured in Hz (Yocto-3D-V2 only).
 *
 * @return an integer corresponding to the measure update frequency, measured in Hz (Yocto-3D-V2 only)
 *
 * On failure, throws an exception or returns Y_BANDWIDTH_INVALID.
 */
-(int)     get_bandwidth;


-(int) bandwidth;
/**
 * Changes the measure update frequency, measured in Hz (Yocto-3D-V2 only). When the
 * frequency is lower, the device performs averaging.
 *
 * @param newval : an integer corresponding to the measure update frequency, measured in Hz (Yocto-3D-V2 only)
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_bandwidth:(int) newval;
-(int)     setBandwidth:(int) newval;

/**
 * Returns the X component of the acceleration, as a floating point number.
 *
 * @return a floating point number corresponding to the X component of the acceleration, as a floating point number
 *
 * On failure, throws an exception or returns Y_XVALUE_INVALID.
 */
-(double)     get_xValue;


-(double) xValue;
/**
 * Returns the Y component of the acceleration, as a floating point number.
 *
 * @return a floating point number corresponding to the Y component of the acceleration, as a floating point number
 *
 * On failure, throws an exception or returns Y_YVALUE_INVALID.
 */
-(double)     get_yValue;


-(double) yValue;
/**
 * Returns the Z component of the acceleration, as a floating point number.
 *
 * @return a floating point number corresponding to the Z component of the acceleration, as a floating point number
 *
 * On failure, throws an exception or returns Y_ZVALUE_INVALID.
 */
-(double)     get_zValue;


-(double) zValue;
-(Y_GRAVITYCANCELLATION_enum)     get_gravityCancellation;


-(Y_GRAVITYCANCELLATION_enum) gravityCancellation;
-(int)     set_gravityCancellation:(Y_GRAVITYCANCELLATION_enum) newval;
-(int)     setGravityCancellation:(Y_GRAVITYCANCELLATION_enum) newval;

/**
 * Retrieves an accelerometer for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the accelerometer is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YAccelerometer.isOnline() to test if the accelerometer is
 * indeed online at a given time. In case of ambiguity when looking for
 * an accelerometer by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * If a call to this object's is_online() method returns FALSE although
 * you are certain that the matching device is plugged, make sure that you did
 * call registerHub() at application initialization time.
 *
 * @param func : a string that uniquely characterizes the accelerometer
 *
 * @return a YAccelerometer object allowing you to drive the accelerometer.
 */
+(YAccelerometer*)     FindAccelerometer:(NSString*)func;

/**
 * Registers the callback function that is invoked on every change of advertised value.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a nil pointer as argument.
 *
 * @param callback : the callback function to call, or a nil pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and the character string describing
 *         the new advertised value.
 * @noreturn
 */
-(int)     registerValueCallback:(YAccelerometerValueCallback)callback;

-(int)     _invokeValueCallback:(NSString*)value;

/**
 * Registers the callback function that is invoked on every periodic timed notification.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a nil pointer as argument.
 *
 * @param callback : the callback function to call, or a nil pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and an YMeasure object describing
 *         the new advertised value.
 * @noreturn
 */
-(int)     registerTimedReportCallback:(YAccelerometerTimedReportCallback)callback;

-(int)     _invokeTimedReportCallback:(YMeasure*)value;


/**
 * Continues the enumeration of accelerometers started using yFirstAccelerometer().
 *
 * @return a pointer to a YAccelerometer object, corresponding to
 *         an accelerometer currently online, or a nil pointer
 *         if there are no more accelerometers to enumerate.
 */
-(YAccelerometer*) nextAccelerometer;
/**
 * Starts the enumeration of accelerometers currently accessible.
 * Use the method YAccelerometer.nextAccelerometer() to iterate on
 * next accelerometers.
 *
 * @return a pointer to a YAccelerometer object, corresponding to
 *         the first accelerometer currently online, or a nil pointer
 *         if there are none.
 */
+(YAccelerometer*) FirstAccelerometer;
//--- (end of YAccelerometer public methods declaration)

@end

//--- (YAccelerometer functions declaration)
/**
 * Retrieves an accelerometer for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the accelerometer is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YAccelerometer.isOnline() to test if the accelerometer is
 * indeed online at a given time. In case of ambiguity when looking for
 * an accelerometer by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * If a call to this object's is_online() method returns FALSE although
 * you are certain that the matching device is plugged, make sure that you did
 * call registerHub() at application initialization time.
 *
 * @param func : a string that uniquely characterizes the accelerometer
 *
 * @return a YAccelerometer object allowing you to drive the accelerometer.
 */
YAccelerometer* yFindAccelerometer(NSString* func);
/**
 * Starts the enumeration of accelerometers currently accessible.
 * Use the method YAccelerometer.nextAccelerometer() to iterate on
 * next accelerometers.
 *
 * @return a pointer to a YAccelerometer object, corresponding to
 *         the first accelerometer currently online, or a nil pointer
 *         if there are none.
 */
YAccelerometer* yFirstAccelerometer(void);

//--- (end of YAccelerometer functions declaration)
CF_EXTERN_C_END

