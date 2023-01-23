using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1_client
{
    public partial class Form1 : Form
    {
        bool terminating = false;
        bool connected = false;
        Socket clientSocket;


        public Form1()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            this.FormClosing += new FormClosingEventHandler(Form1_FormClosing);
            InitializeComponent();
        }

        private void Receive()
        {
            string incomingMessage = "";
            while (connected)
            {
                
                try
                {
                    Byte[] buffer = new Byte[64];
                    clientSocket.Receive(buffer);

                    incomingMessage = Encoding.Default.GetString(buffer);
                    incomingMessage = incomingMessage.Substring(0, incomingMessage.IndexOf("\0"));
                    logs.AppendText("Server: " + incomingMessage + "\n");

                    string name = textBox_name.Text;
                    string email = textBox_email.Text;

                    int sum = 0;
                    for(int i = 0; i < email.Length; i++)
                    {
                        char digit = incomingMessage[i % incomingMessage.Length];
                        int digit_int = digit - '0';
                        int shifted_ascii_value = email[i] + digit_int;
                        sum = sum + shifted_ascii_value;
                    }
                    

                    string digit_str = sum.ToString();

                    string new_message = digit_str + " " + name;
                    logs.AppendText("Message sent: " + new_message + "\n");

                    Byte[] lastMessage = Encoding.Default.GetBytes(new_message);
                    clientSocket.Send(lastMessage);

                    Byte[] lastServer = new Byte[64];
                    clientSocket.Receive(lastServer);

                    string lastIncome = Encoding.Default.GetString(lastServer);
                    lastIncome = lastIncome.Substring(0, lastIncome.IndexOf("\0"));
                    logs.AppendText("Server: " + lastIncome + "\n\n");
                }
                catch
                {
                    if (!terminating)
                    {
                        logs.AppendText("The server has disconnected\n");
                        button_connect.Enabled = true;
                        
                    }

                    
                }
                clientSocket.Close();
                connected = false;
            }
        }
        private void Form1_FormClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            connected = false;
            terminating = true;
            Environment.Exit(0);
        }
        private void button_connect_Click(object sender, EventArgs e)
        {
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            string IP = textBox_ip.Text;
            string name = textBox_name.Text;
            string email = textBox_email.Text;
            string message = email + " " + name;

            int portNum;
            if (Int32.TryParse(textBox_port.Text, out portNum))
            {
                try
                {
                    clientSocket.Connect(IP, portNum);
                    logs.Enabled = true;
                    connected = true;
                    logs.AppendText("Connection established...\n");

                    Byte[] buffer = Encoding.Default.GetBytes(message);
                    clientSocket.Send(buffer);

                    logs.AppendText("Message sent: " + message + "\n");

                    Thread receiveThread = new Thread(Receive);
                    receiveThread.Start();

                }
                catch
                {
                    logs.AppendText("Problem occured while connecting...\n");
                }
            }
            else
            {
                logs.AppendText("Wrong port specified!\n");
            }

        }
    }
}
