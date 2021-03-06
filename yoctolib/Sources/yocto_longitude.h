/*********************************************************************
 *
 * $Id: yocto_longitude.h 31436 2018-08-07 15:28:18Z seb $
 *
 * Declares yFindLongitude(), the high-level API for Longitude functions
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

@class YLongitude;

//--- (YLongitude globals)
typedef void (*YLongitudeValueCallback)(YLongitude *func, NSString *functionValue);
typedef void (*YLongitudeTimedReportCallback)(YLongitude *func, YMeasure *measure);
//--- (end of YLongitude globals)

//--- (YLongitude class start)
/**
 * YLongitude Class: Longitude function interface
 *
 * The Yoctopuce class YLongitude allows you to read the longitude from Yoctopuce
 * geolocalization sensors. It inherits from the YSensor class the core functions to
 * read measurements, register callback functions, access the autonomous
 * datalogger.
 */
@interface YLongitude : YSensor
//--- (end of YLongitude class start)
{
@protected
//--- (YLongitude attributes declaration)
    YLongitudeValueCallback _valueCallbackLongitude;
    YLongitudeTimedReportCallback _timedReportCallbackLongitude;
//--- (end of YLongitude attributes declaration)
}
// Constructor is protected, use yFindLongitude factory function to instantiate
-(id)    initWith:(NSString*) func;

//--- (YLongitude private methods declaration)
// Function-specific method for parsing of JSON output and caching result
-(int)             _parseAttr:(yJsonStateMachine*) j;

//--- (end of YLongitude private methods declaration)
//--- (YLongitude yapiwrapper declaration)
//--- (end of YLongitude yapiwrapper declaration)
//--- (YLongitude public methods declaration)
/**
 * Retrieves a longitude sensor for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the longitude sensor is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YLongitude.isOnline() to test if the longitude sensor is
 * indeed online at a given time. In case of ambiguity when looking for
 * a longitude sensor by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * If a call to this object's is_online() method returns FALSE although
 * you are certain that the matching device is plugged, make sure that you did
 * call registerHub() at application initialization time.
 *
 * @param func : a string that uniquely characterizes the longitude sensor
 *
 * @return a YLongitude object allowing you to drive the longitude sensor.
 */
+(YLongitude*)     FindLongitude:(NSString*)func;

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
-(int)     registerValueCallback:(YLongitudeValueCallback)callback;

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
-(int)     registerTimedReportCallback:(YLongitudeTimedReportCallback)callback;

-(int)     _invokeTimedReportCallback:(YMeasure*)value;


/**
 * Continues the enumeration of longitude sensors started using yFirstLongitude().
 *
 * @return a pointer to a YLongitude object, corresponding to
 *         a longitude sensor currently online, or a nil pointer
 *         if there are no more longitude sensors to enumerate.
 */
-(YLongitude*) nextLongitude;
/**
 * Starts the enumeration of longitude sensors currently accessible.
 * Use the method YLongitude.nextLongitude() to iterate on
 * next longitude sensors.
 *
 * @return a pointer to a YLongitude object, corresponding to
 *         the first longitude sensor currently online, or a nil pointer
 *         if there are none.
 */
+(YLongitude*) FirstLongitude;
//--- (end of YLongitude public methods declaration)

@end

//--- (YLongitude functions declaration)
/**
 * Retrieves a longitude sensor for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the longitude sensor is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YLongitude.isOnline() to test if the longitude sensor is
 * indeed online at a given time. In case of ambiguity when looking for
 * a longitude sensor by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * If a call to this object's is_online() method returns FALSE although
 * you are certain that the matching device is plugged, make sure that you did
 * call registerHub() at application initialization time.
 *
 * @param func : a string that uniquely characterizes the longitude sensor
 *
 * @return a YLongitude object allowing you to drive the longitude sensor.
 */
YLongitude* yFindLongitude(NSString* func);
/**
 * Starts the enumeration of longitude sensors currently accessible.
 * Use the method YLongitude.nextLongitude() to iterate on
 * next longitude sensors.
 *
 * @return a pointer to a YLongitude object, corresponding to
 *         the first longitude sensor currently online, or a nil pointer
 *         if there are none.
 */
YLongitude* yFirstLongitude(void);

//--- (end of YLongitude functions declaration)
CF_EXTERN_C_END

