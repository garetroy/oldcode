"""
This is the gui for craiggrabber

Requires:
	tkinter
	craiggrabber

Future Plans:
	Making this into a class
	Making it pretty
	Multi-threaded
"""
import os, urllib, urllib.request
from tkinter import Label, Entry, filedialog, Button, messagebox, Tk, StringVar
from craiggrabber import login_session, generalwebpageparser, user_type

root_frame = Tk()
path_var = StringVar()
path_var.set('')
Label(root_frame, text="Enter the data").grid(row=0, column=1)
Label(root_frame, text="Directory to copy to:").grid(row=2)
Label(root_frame, text="Url:").grid(row=3)
path_entry = Entry(root_frame, textvariable=path_var)
url_entry = Entry(root_frame)

path_entry.grid(row=2, column=1)
url_entry.grid(row=3, column=1)


def next_step():
	"""
	This function checks to see if the path or the url is back

	Returns:
		None
	"""
	if os.path.isdir(str(path_entry.get())):
		os.chdir(str(path_entry.get()))
	else:
		messagebox.showinfo("Bad Path", "This Path is invalid")
		return
	try:
		urllib.request.urlopen(str(url_entry.get()))
	except ValueError:
		messagebox.showinfo("Bad Url", "This is an invalid Url")
		return
	isaccount = user_type(str(url_entry.get()))
	if isaccount == 500:
		messagebox.showinfo("Bad Url", "This is not a page with craiglist items")
		return

	site = urllib.request.urlopen(str(url_entry.get()))
	start_scrape(isaccount, str(url_entry.get()), site)

def getting_path():
	"""
	This is the function to get the directory when browsing through files (when browse button is
	clicked)
	"""
	directory = filedialog.askdirectory()
	path_var.set(directory)

def start_scrape(isaccount, url, site):
	"""
	This starts the scrape, if it is an account, then it creates two labels and entry and a button
	for users to enter their login info then gets that input and gives it to login_trial
	"""
	global root_frame
	if isaccount:
		Label(root_frame, text="Enter Username:").grid(row=6)
		Label(root_frame, text="Enter Password:").grid(row=7)
		user_ent = StringVar(root_frame)
		username_ent = Entry(root_frame, textvariable=user_ent)
		pass_ent = StringVar(root_frame)
		password_ent = Entry(root_frame, show="*", textvariable=pass_ent)
		username_ent.grid(row=6, column=2)
		password_ent.grid(row=7, column=2)
		Button(root_frame, text='Next', command=(lambda: login_trial(user_ent.get(), pass_ent.get(), url))).grid(row=9, column=1)
	else:
		generalwebpageparser(site, url)

def login_trial(username, password, url):
	"""
	This tests the login to see if it is a working login.
	"""
	if len(username) != 0:
		success = login_session(username, password, url, True)
		if success:
			messagebox.showinfo("Success!", "Logged in, will start process!")
			success = login_session(username, password, url)
		if not success:
			messagebox.showinfo("Oh no!", "Login seems not to be correct")



next_btn = Button(root_frame, text='Go', command=next_step)
directory_btn = Button(root_frame, text='Browse...', command=getting_path)

directory_btn.grid(row=2, column=3)
next_btn.grid(row=5, column=1)


if __name__ == '__main__':
	root_frame.mainloop()
