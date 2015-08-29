//
//  WeatherServiceController.swift
//  weatheralerts
//
//  Created by Steve McHugh on 8/28/15.
//  Copyright (c) 2015 chugs. All rights reserved.
//

import Foundation

class WeatherServiceController : NSObject {
    
    override init() {
        super.init()
        NSNotificationCenter.defaultCenter().addObserver(
            self, selector: "locationAvailable:", name: "LOCATION_AVAILABLE", object: nil
        )
    }
    
    func locationAvailable(notification:NSNotification) -> Void {
        let userInfo = notification.userInfo as! Dictionary<String,String>
        
        println("WeatherService:  Location available \(userInfo)")
        
    }
    
}
