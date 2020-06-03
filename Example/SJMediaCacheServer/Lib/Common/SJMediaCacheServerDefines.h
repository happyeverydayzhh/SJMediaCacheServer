//
//  SJMediaCacheServerDefines.h
//  SJMediaCacheServer
//
//  Created by BlueDancer on 2020/5/30.
//  Copyright © 2020 changsanjiang@gmail.com. All rights reserved.
//

#ifndef SJMediaCacheServerDefines_h
#define SJMediaCacheServerDefines_h
#import <Foundation/Foundation.h>
#import "SJDataRequest.h"
@protocol SJDataResponseDelegate, SJResourcePartialContentReaderDelegate;
@protocol SJResourceReaderDelegate;

NS_ASSUME_NONNULL_BEGIN
@protocol SJURLConvertor <NSObject>
- (nullable NSURL *)proxyURLWithURL:(NSURL *)URL localServerURL:(NSURL *)serverURL;
- (nullable NSURL *)URLWithProxyURL:(NSURL *)proxyURL;
- (nullable NSString *)resourceNameWithURL:(NSURL *)URL;
@end

@protocol SJDataResponse <NSObject>
- (instancetype)initWithRequest:(SJDataRequest *)request delegate:(id<SJDataResponseDelegate>)delegate;

- (void)prepare;
@property (nonatomic, readonly) NSUInteger contentLength;
- (nullable NSData *)readDataOfLength:(NSUInteger)length;
@property (nonatomic, readonly) NSUInteger offset;
@property (nonatomic, readonly) BOOL isDone;
- (void)close;
@end

@protocol SJDataResponseDelegate <NSObject>
- (void)responsePrepareDidFinish:(id<SJDataResponse>)response;
- (void)responseHasAvailableData:(id<SJDataResponse>)response;
- (void)response:(id<SJDataResponse>)response anErrorOccurred:(NSError *)error;
@end
 
#pragma mark -

@protocol SJResourceReader <NSObject>
@property (nonatomic, weak, nullable) id<SJResourceReaderDelegate> delegate;

- (void)prepare;
@property (nonatomic, readonly) NSUInteger contentLength;
@property (nonatomic, readonly) NSUInteger offset;
- (nullable NSData *)readDataOfLength:(NSUInteger)length;
@property (nonatomic, readonly) BOOL isReadingEndOfData;
- (void)close;
@end

@protocol SJResourceReaderDelegate <NSObject>
- (void)readerPrepareDidFinish:(id<SJResourceReader>)reader;
- (void)readerHasAvailableData:(id<SJResourceReader>)reader;
- (void)reader:(id<SJResourceReader>)reader anErrorOccurred:(NSError *)error;
@end


@protocol SJResource <NSObject>
+ (instancetype)resourceWithURL:(NSURL *)URL;
 
- (id<SJResourceReader>)readDataWithRequest:(SJDataRequest *)request;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END

#endif /* SJMediaCacheServerDefines_h */
