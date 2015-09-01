//
//  PushNotificationController.swift
//  weatheralerts
//
//  Created by Steve McHugh on 8/28/15.
//  Copyright (c) 2015 chugs. All rights reserved.
//

import Foundation
import Parse

class PushNotificationController : NSObject {
    
    override init() {
        super.init()
        
        let parseApplicationId = valueForAPIKey(keyname: "PARSE_APPLICATION_ID")
        let parseClientKey     = valueForAPIKey(keyname: "PARSE_CLIENT_KEY")
        
        Parse.setApplicationId(parseApplicationId, clientKey: parseClientKey)
        
        NSNotificationCenter.defaultCenter().addObserver(self,
            selector: "advisoryAvailable:",
            name: "ADVISORY_AVAILABLE",
            object: nil)
    }
    
    func advisoryAvailable(notification:NSNotification) -> Void {
        
        println("advisoryAvailable")
        
        // Get our advisory name
        let userInfo = notification.userInfo as! Dictionary<String,String>
        
        let advisoryLocation = userInfo["location"]!
        let advisoryName     = userInfo["name"]!
        
        let pushMessage = "Weather Advisory for \(advisoryLocation):  \(advisoryName)"
        
        // Create our Installation query
        let token = PFInstallation.currentInstallation().deviceToken
        let pushQuery:PFQuery = PFInstallation.query()!
        pushQuery.whereKey("deviceToken", equalTo:token!)
        
        // Send push notification to query
        let pushNotification:PFPush = PFPush()
        pushNotification.setQuery(pushQuery)
        pushNotification.setData([
            "sound":"alert.caf",
            "alert":pushMessage
            ])
        pushNotification.sendPushInBackgroundWithBlock({ (succeeded,e) -> Void in
            
            if succeeded {
                println("Push message to query in background succeeded")
            }
            if let error = e {
                println("Error:  \(error.localizedDescription)")
            }
        })
    }
    
}
