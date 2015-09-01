//
//  AFGeographicObjectConnector.h
//  Aeris
//
//  Created by Nicholas Shipes on 9/5/13.
//  Copyright (c) 2013 HAMweather, LLC. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

#import <Aeris/AWFObjectLoader.h>
#import <Aeris/AWFGlobals.h>

@class AWFPlace, AWFGeoPolygon, AWFRequestOptions;

/**
 *  `AWFGeographicObjectLoader` is a subclass of `AWFObjectLoader` that provides additional utility methods for requesting API data
 *  that is based on a geographic location or region. This class should not be used as is, but rather should be subclassed to provided the
 *	required configuration for interacting with the API.
 */
@interface AWFGeographicObjectLoader : AWFObjectLoader

/**
 *  Requests objects for the specific place. The place must be a valid `AWFPlace` instance.
 *
 *  @param place   The place to use for the request.
 *  @param options An `AWFRequestOptions` instance containing additional parameters to be used with the request (optional).
 *  @param success The block to be executed on the completion of a successful request. This block has no return value and takes two
 *		arguments: the receiver object loader and an array of associated `AWFObject` instances returned by the request.
 *  @param failure The block to be executed on the failed or unsuccessful request. This block has no return value and takes two arguments:
 *		the receiver object loader and the error that occurred during the request.
 */
- (void)getForPlace:(AWFPlace *)place
            options:(AWFRequestOptions *)options
         completion:(AWFObjectLoaderCompletionBlock)completionBlock;

/**
 *  Requests objects within a circle defined by a center at the specific place's coordinate and a radius. The place must be a valid
 *  `AWFPlace` instance.
 *
 *  @param place   The place to use for the request.
 *  @param radius  The radius from the place's coordinate to include results for. Radius should be provided as a valid distance string,
 *		(e.g., `@"50mi"` or `@"100km"`). If no radius is provided, the default of `@"25mi"` will be used.
 *  @param options An `AWFRequestOptions` instance containing additional parameters to be used with the request (optional).
 *  @param success The block to be executed on the completion of a successful request. This block has no return value and takes two
 *		arguments: the receiver object loader and an array of associated `AWFObject` instances returned by the request.
 *  @param failure The block to be executed on the failed or unsuccessful request. This block has no return value and takes two arguments:
 *		the receiver object loader and the error that occurred during the request.
 */
- (void)getClosestToPlace:(AWFPlace *)place
                   radius:(NSString *)radius
                  options:(AWFRequestOptions *)options
               completion:(AWFObjectLoaderCompletionBlock)completionBlock;

/**
 *  Requests objects within a bounding box defined by top-left and bottom-right coordinates.
 *
 *  @param northwestCoordinate The top-left coordinate of the bounding box.
 *  @param southeastCoordinate The bottom-right coordinate of the bounding box.
 *  @param options             An `AWFRequestOptions` instance containing additional parameters to be used with the request (optional).
 *  @param success             The block to be executed on the completion of a successful request. This block has no return value and takes
 *		two arguments: the receiver object loader and an array of associated `AWFObject` instances returned by the request.
 *  @param failure             The block to be executed on the failed or unsuccessful request. This block has no return value and takes two
 *		arguments: the receiver object loader and the error that occurred during the request.
 */
- (void)getWithinBoundsFromNorthwestCoordinate:(CLLocationCoordinate2D)northwestCoordinate
                           southeastCoordinate:(CLLocationCoordinate2D)southeastCoordinate
                                       options:(AWFRequestOptions *)options
                                    completion:(AWFObjectLoaderCompletionBlock)completionBlock;

/**
 *  Requests objects within an irregular polygon defined by the a series of coordinates. The specified polygon must be a valid
 *  `AWFGeoPolygon` instance.
 *
 *  @param polygon The polygon
 *  @param options An `AWFRequestOptions` instance containing additional parameters to be used with the request (optional).
 *  @param success The block to be executed on the completion of a successful request. This block has no return value and takes two
 *		arguments: the receiver object loader and an array of associated `AWFObject` instances returned by the request.
 *  @param failure The block to be executed on the failed or unsuccessful request. This block has no return value and takes two arguments:
 *		the receiver object loader and the error that occurred during the request.
 *  @see `AWFGeoPolygon`
 */
- (void)getWithinPolygon:(AWFGeoPolygon *)polygon
                 options:(AWFRequestOptions *)options
              completion:(AWFObjectLoaderCompletionBlock)completionBlock;

//-------------------------
// @name Deprecated Methods
//-------------------------

/**
 *  Requests data from the API for the specified place.
 *
 *  @param place   The `AWFPlace` from which to return data for.
 *  @param options An optional dictionary containing additional parameters to be used with the request.
 *	@deprecated    As of version 1.2, replaced by 'getForPlace:options:success:failure:'
 */
- (void)requestForPlace:(AWFPlace *)place options:(NSDictionary *)options AWF_DEPRECATED("Deprecated as of 2.0.0, use getForPlace:options:success:failure: instead.");

/**
 *  Requests data closest to the specified place.
 *
 *  @param place   The `AWFPlace` from which to search for nearby data from.
 *  @param options An optional dictionary containing additional parameters to be used with the request.
 *	@deprecated    As of version 1.2, replaced by 'getClosestToPlace:options:success:failure:'
 */
- (void)requestClosest:(AWFPlace *)place options:(NSDictionary *)options AWF_DEPRECATED("Deprecated as of 2.0.0, use getClosestToPlace:options:success:failure: instead.");

/**
 *  Requests all data objects within the polygon bounded by the specified points.
 *
 *  @param points  An array of coordinate points defining the polygon to search within.
 *  @param options An optional dictionary containing additional parameters to be used with the request.
 *	@deprecated    As of version 1.2, replaced by 'getWithinPolygon:options:success:failure:'
 */
- (void)requestWithinPolygon:(NSArray *)points options:(NSDictionary *)options AWF_DEPRECATED("Deprecated as of 2.0.0, use getWithinPolygon:options:success:failure: instead.");

/**
 *  Requests all data objects within the bounding box defined by northwest and southeast coordinate.
 *
 *  @param northwestCoordinate The northwest coordinate, or top-left corner, of the bounding box to search within
 *  @param southeastCoordinate The southeast coordinate, or bottom-right corner, of the bounding box to search within
 *  @param options             An optional dictionary containing additional parameters to be used with the request.
 *	@deprecated                As of version 1.2, replaced by
 *		'getWithinBoundsFromNorthwestCoordinate:southeastCoordinate:options:success:failure:'
 */
- (void)requestWithinBoundsFromNorthwestCoordinate:(CLLocationCoordinate2D)northwestCoordinate southeastCoordinate:(CLLocationCoordinate2D)southeastCoordinate
                                           options:(NSDictionary *)options AWF_DEPRECATED("Deprecated as of 2.0.0, use getWithinBoundsFromNorthwestCoordinate:southeastCoordinate:options:success:failure: instead");

@end