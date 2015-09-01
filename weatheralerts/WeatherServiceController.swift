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
        
        let aerisConsumerId = valueForAPIKey(keyname: "AERIS_CONSUMER_ID")
        let aerisConsumerSecret = valueForAPIKey(keyname: "AERIS_CONSUMER_SECRET")
        
        AerisEngine.engineWithKey(aerisConsumerId, secret: aerisConsumerSecret)
        
        NSNotificationCenter.defaultCenter().addObserver(self,
            selector: "locationAvailable:",
            name: "LOCATION_AVAILABLE",
            object: nil)
    }
    
    func locationAvailable(notification:NSNotification) -> Void {
        let userInfo = notification.userInfo as! Dictionary<String,String>
        
        println("WeatherService:  Location available \(userInfo)")
        
        let city    = userInfo["city"]!
        let state   = userInfo["state"]!
        let country = userInfo["country"]!
        
        let place = AWFPlace(city: city, state: state, country: country)
        let advisoryLoader = AWFAdvisoriesLoader()
        
        advisoryLoader.getAdvisoriesForPlace(place, options: nil) { (advisories, e) -> Void in
            if let error = e {
                println("Error:  \(error.localizedDescription)")
            } else {
                // Take the last advisory
                if let advisory = advisories.last as? AWFAdvisory {
                    
                    let userInfo = [
                        "location":  city + ", " + state,
                        "name":  advisory.name,
                        "body":  advisory.body
                    ]
                    
                    NSNotificationCenter.defaultCenter().postNotificationName("ADVISORY_AVAILABLE",
                        object: nil,
                        userInfo: userInfo)
                } else {
                    println("no advisories")
                }
            }
        }
        
    }
    
}
