# KEEP_ISP

Keep ISP is a program originally published in the book "Web Site Construction Kit for Windows 95" by Scott Zimmerman.

I have taken this code which was put into the public domain, posted it on Github, and added a Makefile for Borland C++ 5.5 in the directory BCC55.

An extract from chapter 16 of the book describing this program is below:

> ## Keeping the Connection Alive
>
> After you have connected to your service provider, it is possible that your connection could drop. This could happen for various reasons. For example, your service provider might allow your connection to time out after a certain period of inactivity.
>
> **Listing 16.1. Keep_ISP.cpp is a simple hack to let your ISP know your server is still there.**
>
See src/keep_isp.cpp for Listing 16.1.
>
> Listing 16.1 shows a Windows C++ program that will solve this problem. Keep\_ISP is a program that will ping a given IP address every 12 minutes, by default. Most service providers set their ports to time out after 15 to 20 minutes of inactivity. If you expect that your service provider has a policy of letting inactive connections time out, you should keep this program running in the background to avoid problems. Both the source code and the compiled program are included on the CD-ROM in the \tools\keep\_isp directory. You need not study the source code if you would rather not dig into C++. The program has been compiled with Visual C++ 4.0 as a 32-bit GUI application. It runs minimized as an icon by default.
>
> Presuming an understanding of the Windows API such as that gained from a careful reading of the classic book "Programming Windows 3.1," by Charles Petzold, the only moderately interesting code in this program occurs in the WndProc function. Keep\_ISP uses the WM\_CREATE message to start a Windows timer, which will call back every minute. Since the SetTimer API requires a 16-bit integer parameter for the time interval in milliseconds, the largest value you can pass is just over one minute. Here, we ask Windows to count 60,000 milliseconds and we will keep track of the minutes for ourselves. The code for the WM_TIMER message checks if the number of minutes has elapsed, and if so, it executes a ping to the ISP and resets the elapsed time counter back to zero.
>
> Very little error-checking is performed in Keep_ISP. For example, it assumes that ping.exe exists somewhere in the path. Feel free to enhance it and/or distribute it; it is public domain freeware.
>
> Keep_ISP accepts three command-line arguments, which it scans for in the WinMain function. The arguments must appear in lowercase. The first two parameters are optional. The third parameter must be present, and it must always be last on the command line.
>
> * -b Beep each time ping is executed.
>
> * -nx Number of minutes (x) to pause between pings.
>
> * -aIP The IP address of the gateway server at your ISP.
>
> For example:
>
> `keep_isp -b -n15 -a123.123.123.123`
>
> In this case, beeping is turned on and the interval is set for 15 minutes. You can place a shortcut to this program in your \Windows\Start Menu\Programs\StartUp folder. Then use Explorer to right-click it, choose Properties, select the Shortcut tab, and enter the full path and command-line parameters in the text box labeled Target. See Figure 16.2 for an example of this.
