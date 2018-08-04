#include <bits/stdc++.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
using namespace std;
void print_caps_lock_state(int state)
{
    printf("Caps Lock state: %s (%d)\n",
           state & K_CAPSLOCK == K_CAPSLOCK ? "on" : "off", state);
}

int main(void)
{
    int fd = open("/dev/tty0", O_NOCTTY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    int state = 0;
    // Get the keyboard state into the state variable.                          
    if (-1 == ioctl(fd, KDGKBLED, &state))
    {
        perror("ioctl");
        close(fd);
        return -1;
    }

    print_caps_lock_state(state);

    // Toggle the caps lock state                                               
    state ^= K_CAPSLOCK;

    // Set the new state                                                        
    if (-1 == ioctl(fd, KDSKBLED, state))
    {
        perror("ioctl set");
        close(fd);
        return -1;
    }

    // Get the new state                                                        
    state = 0;
    if (-1 == ioctl(fd, KDGKBLED, &state))
    {
        perror("ioctl");
        close(fd);
        return -1;
    }

    print_caps_lock_state(state);

    close(fd);
    return 0;
}
