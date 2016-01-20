/* Synthesize Singleton For Class
 *
 * Creates a singleton interface for the specified class with the following methods:
 *
 * + (MyClass*) sharedInstance;
 *
 * Calling sharedInstance will instantiate the class and swizzle some methods to ensure
 * that only a single instance ever exists.
 * Calling releaseInstance will destroy the shared instance and return the swizzled
 * methods to their former selves.
 *
 *
 * Usage:
 *
 * MyClass.h:
 * ========================================
 *	#import "FSSingleton.h"
 *
 *	@interface MyClass: SomeSuperclass
 *	{
 *		...
 *	}
 *	YP_DECLEAR_AS_SINGLETON;
 *
 *	@end
 * ========================================
 *
 *
 *	MyClass.m:
 * ========================================
 *	#import "MyClass.h"
 *
 *	@implementation MyClass
 *
 *  YP_IMPLEMENT_SINGLETON(MyClass);
 *
 *	...
 *
 *	@end
 * ========================================
 */

#ifndef YPSingleton_h
#define YPSingleton_h

#import <objc/runtime.h>

//-------------------------------------------------------------------------------
#define YP_DECLEAR_AS_SINGLETON                                                 \
+ (instancetype)sharedInstance;

//-------------------------------------------------------------------------------

#define YP_IMPLEMENT_SINGLETON(__CLASS_NAME__)                                  \
                                                                                \
+ (instancetype)sharedInstance                                                  \
{                                                                               \
    static __CLASS_NAME__* g_sharedInstance = nil;                              \
    static dispatch_once_t onceToken;                                           \
    dispatch_once(&onceToken, ^{                                                \
        g_sharedInstance = [[__CLASS_NAME__ alloc] init];                       \
    });                                                                         \
    return g_sharedInstance;                                                    \
}                                                                               \
                                                                                \
+ (id)allocWithZone:(NSZone*)zone                                               \
{                                                                               \
    [NSException raise:@"YPSingleton"                                           \
                format:@"Cannot alloc singleton, sharedInstance must be used."];\
    return nil;                                                                 \
}                                                                               \
                                                                                \
- (id)copyWithZone:(NSZone *)zone                                               \
{                                                                               \
    [NSException raise:@"YPSingleton"                                           \
                format:@"Cannot copy singleton, sharedInstance must be used."]; \
    return nil;                                                                 \
}

#endif
