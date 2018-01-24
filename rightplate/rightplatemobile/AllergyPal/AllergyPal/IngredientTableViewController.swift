//
//  IngredientTableViewController.swift
//  AllergyPal
//
//  Created by Cody Hatfield on 11/15/15.
//  Copyright © 2015 Cody Hatfield. All rights reserved.
//

import UIKit

class IngredientTableViewController: UITableViewController {
	
	var objects : [AnyObject] = ["Peanuts"]
	var data = ["Peanuts", "Almonds"]
	
    override func viewDidLoad() {
        super.viewDidLoad()
		
		self.navigationItem.leftBarButtonItem = self.editButtonItem()
		
		let addButton = UIBarButtonItem(barButtonSystemItem: .Add, target: self, action: "insertNewObject:")
		self.navigationItem.rightBarButtonItem = addButton
		
		self.navigationItem.title = "THE RIGHT PLATE"
		
		
		self.navigationController?.navigationBar.titleTextAttributes = [NSFontAttributeName: UIFont(name: "Archer", size: 22)!, NSForegroundColorAttributeName: UIColor.whiteColor()]
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

	func insertNewObject(sender: AnyObject) {
		objects.insert(data[objects.count%data.count], atIndex: 0)
		let indexPath = NSIndexPath(forRow: 0, inSection: 0)
		self.tableView.insertRowsAtIndexPaths([indexPath], withRowAnimation: .Automatic)
	}
	
	// MARK: - Table View
	
	override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
		return 1
	}
	
	override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return objects.count
	}
	
	override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCellWithIdentifier("cell", forIndexPath: indexPath)
		
		let object = objects[indexPath.row] as! String
		cell.textLabel!.text = object
		return cell
	}
	
	override func tableView(tableView: UITableView, canEditRowAtIndexPath indexPath: NSIndexPath) -> Bool {
		// Return false if you do not want the specified item to be editable.
		return true
	}
	
	override func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath) {
		if editingStyle == .Delete {
			objects.removeAtIndex(indexPath.row)
			tableView.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Fade)
		} else if editingStyle == .Insert {
			// Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
		}
	}
	
	override func preferredStatusBarStyle() -> UIStatusBarStyle {
		return UIStatusBarStyle.LightContent
	}

}
