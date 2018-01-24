//
//  FirstViewController.swift
//  AllergyPal
//
//  Created by Cody Hatfield on 11/14/15.
//  Copyright © 2015 Cody Hatfield. All rights reserved.
//

import UIKit

class AddDataViewController: UIViewController {
	
	var scanner : MTBBarcodeScanner?
	
	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
	
		scanner = MTBBarcodeScanner(previewView: self.view)
		MTBBarcodeScanner.requestCameraPermissionWithSuccess({(success: Bool) in
			
		})
		
	}
	
	override func viewDidAppear(animated: Bool) {
		if let scanner = self.scanner{
			scanner.startScanningWithResultBlock({(codes: [AnyObject]!) in
				let code = codes[0] as! AVMetadataMachineReadableCodeObject
				print(code.stringValue)
				self.scanner?.stopScanning()
				if code.stringValue == "0038000359217"{
					self.performSegueWithIdentifier("showModalRC", sender: self)
				}
				else{
					self.performSegueWithIdentifier("showModalP", sender: self)
				}
			})
		}
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}


}

