using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Web;
using System.Data.SqlTypes;

namespace Server
{
	public partial class Form1 : Form
	{

		// variables used for hte project 
		String[] lines;
		bool terminating = false;
		bool listening = false;
		bool question = false;
		int question_num;
		uint max_num_of_clients = 2;
		uint num_of_players = 0;

		Socket server_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

		List<Socket> client_sockets = new List<Socket>();
		List<Socket> gaming_client_sockets = new List<Socket>();
		List<String> client_names = new List<String>();
		List<String> gaming_client_names = new List<String>();
		List<String> observer_names = new List<String>();
		bool game_started = false;

		// Semaphore first_sem = new // Semaphore(0, 3); //  for step one 3 is known 
		// Semaphore sem = new // Semaphore(0, 2); // 2 is the number of players 

		Dictionary<String, float> player_scores = new Dictionary<String, float>();
		Dictionary<String, int> name_to_answer = new Dictionary<String, int>();
		Dictionary<Socket, String> socket_to_name = new Dictionary<Socket, String>();
		List<Thread> current_threads = new List<Thread>();

		public Form1()
		{
			Control.CheckForIllegalCrossThreadCalls = false;
			game_started = false;
			Thread.CurrentThread.Name = "main";
			this.FormClosing += new FormClosingEventHandler(Form1_FormClosing);
			InitializeComponent();
		}
		// listen for the incoming connections
		private void Accept()
		{
			
			while (listening)
			{
				try
				{
					Socket newClient = server_socket.Accept();
					client_sockets.Add(newClient);

					Byte[] buffer = new Byte[64];
					string this_threads_name;
					newClient.Receive(buffer);
					// block untill new connection 
					this_threads_name = Encoding.Default.GetString(buffer);
					this_threads_name = this_threads_name.Substring(0, this_threads_name.IndexOf("\0"));
					//check if a client with the same name is connected
					/* this check used to check if there were two players, if that were the case, the server would not accept the second player
					if(client_names.Count() >= 2)
					{
						Byte[] players_statu = Encoding.Default.GetBytes("There are already two players in the game!");
						try
						{
							newClient.Send(players_statu);
						}
						catch
						{
							logs.AppendText("There is a problem! Check the connection...\n");
							// if client is disconnected, do stuff here 
						}
						client_sockets.Remove(newClient);
						newClient.Close();


						logs.AppendText("A client with the name: " + this_threads_name + " tried to join while the game was running.\n");
					}
					*/
					//if a client with the same name tries to connect 
					if (client_names.Contains(this_threads_name))
					{
						Byte[] name_statu = Encoding.Default.GetBytes("this name is taken!");
						try
						{
							newClient.Send(name_statu);
						}
						catch
						{
							logs.AppendText("There is a problem! Check the connection...\n");
							// if client is disconnected, do stuff here 
						}
						client_sockets.Remove(newClient);
						newClient.Close();
						logs.AppendText("Existing clients name: " + this_threads_name + " there was already someone with this name, so the new client was disconnected.\n");
					}
					//client successfully connects
					else
					{
						Byte[] name_statu = Encoding.Default.GetBytes("this name is not taken !");
						try
						{
							newClient.Send(name_statu);
							client_names.Add(this_threads_name);
							socket_to_name[newClient] = this_threads_name;
							//if the game hasn't started yet the player who joined will be able to play the game
							if (!game_started)
							{
								Thread check_thread = new Thread(() => check_user(newClient));
								check_thread.Start();
								check_thread.Name = "check_disconnect_thread";
								gaming_client_names.Add(this_threads_name);
								//second client
								gaming_client_sockets.Add(newClient);
								logs.AppendText("Client with name " + this_threads_name + " is connected as a player!\n");
							}
							else
							{
								logs.AppendText("Client with name " + this_threads_name + " is connected as an observer!\n");
								Byte[] game_stat = Encoding.Default.GetBytes("A game is in progress please wait until it is over! \n");
								newClient.Send(game_stat);
								observer_names.Add(this_threads_name);
							}
							//num_of_players++;

							//start thread 
							//Thread receiveThread = new Thread(() => Receive(newClient, this_threads_name)); // updated
							//first_sem.Release();// #UP							
							//receiveThread.Start();
							//current_threads.Add(receiveThread);
						}
						catch
						{
							logs.AppendText("There is a problem! Check the connection...\n");
							// if client is disconnected, do stuff here 
						}
					}
				}
				catch
				{
					if (terminating)
					{
						listening = false;
					}
					else
					{
						logs.AppendText("The socket stopped working.\n");
					}
				}
			}
		}

		private void check_user(Socket client)
		{
			while (!game_started)
			{

				Thread.Sleep(250);
				//mddle" status" + client.Connected+
				Byte[] question__ = Encoding.Default.GetBytes("PDONOT");

				try
				{
					client.Send(question__);//update the connected status

				}
				catch
				{
					logs.AppendText("Could not send this  \n");
				}


				if (!client.Connected)
				{
					debug_logs.AppendText("Client disconnected" + socket_to_name[client] + "status" + client.Connected + "\n");
					//remove client from client_sockets, gaming_client_sockets, client_names, gaming_client_names
					client_sockets.Remove(client);
					gaming_client_sockets.Remove(client);
					client_names.Remove(socket_to_name[client]);
					gaming_client_names.Remove(socket_to_name[client]);
					
					Thread.Sleep(250);

					break;


				}



			}
			debug_logs.AppendText("ending check users for user" + socket_to_name[client] + "\n");

		}

		/*
		private void Receive(Socket thisClient , String name ) // updated
		{
			bool connected = true;
			// syncronized with hte game loop by the use of // Semaphores 
			while (connected && !terminating)
			{
				try
				{
					Byte[] buffer = new Byte[64];
					thisClient.Receive(buffer);
					// block untill recive 
					string incomingMessage = Encoding.Default.GetString(buffer);
					incomingMessage = incomingMessage.Substring(0, incomingMessage.IndexOf("\0"));
					logs.AppendText("Client " + name + " : " + incomingMessage + "\n");

					int clients_ans;
					if (Int32.TryParse(incomingMessage, out clients_ans))
					{
						ans[name] = clients_ans;
					}
					else
					{
						logs.AppendText("something went very wrong number should have been send from client \n");
					}
				}
				catch
				{
					connected = false;
					// One user terminated, other user should win the game
					if (!terminating)
					{
						logs.AppendText("A client " + name + " has disconnected\n");
						num_of_players--;
					}
					ans[name] = -1;
					try
					{
						thisClient.Close();
					}catch
					{

					}
					//client_sockets.Remove(thisClient);
					//client_names.Remove(name);
					//broadcast("User");		

				}
				finally
				{
					Thread.Sleep(250);
					sem.Release(); // #UP
					//sem.Release(); // #UP
				}
			}
		}
		*/

		private void Form1_FormClosing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			Environment.Exit(0);
			/*
			foreach (Thread t in current_threads)
			{
				t.Abort();// kill all ch 
			}
			*/
		}
		private void richTextBox1_TextChanged(object sender, EventArgs e)
		{

		}
		private void port_box_TextChanged(object sender, EventArgs e)
		{

		}

		private void launch_button_Click(object sender, EventArgs e)
		{
			//sets the launch parameters 
			int serverPort;

			if (Int32.TryParse(port_box.Text, out serverPort))
			{
				IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, serverPort);
				server_socket.Bind(endPoint);
				server_socket.Listen(5);

				listening = true;
				launch_button.Enabled = false;

				Thread acceptThread = new Thread(Accept);
				acceptThread.Name = "Accept";
				acceptThread.Start();


				logs.AppendText("Started listening on port: " + serverPort + "\n");
			}
			else
			{
				logs.AppendText("Please check port number \n");
			}
		}

		private String[] readFile(String textFile)
		{
			//read the file 
			String[] lines = File.ReadAllLines(textFile);
			return lines;
		}
		// broadcast 
		public void broadcast(string msg)
		{
			debug_logs.AppendText("broadcasting: " + msg + "\n");
			string new_msg = "";
			foreach (Socket cl in client_sockets)
			{
				if (cl.Connected)
				{
					if (gaming_client_sockets.Contains(cl))
					{
						new_msg = "P" + msg;

					}
					else
					{
						new_msg = "O" + msg;
					}
					Byte[] question__ = Encoding.Default.GetBytes(new_msg);

					try
					{
						cl.Send(question__);
					}
					catch
					{
						logs.AppendText("Could not send question \n");
						//client_sockets.Remove(cl);
						// if client is disconnected, do stuff here 
					}
				}
				else
				{
					logs.AppendText("Couldn't send the message due to client socket disconnection: " + socket_to_name[cl]);
				}
			}
			//sleep for msg to arive 
			Thread.Sleep(1000);
		}

		// game loop
		private void game_loop()
		{
			/*first_sem.WaitOne();
			first_sem.WaitOne();
			first_sem.WaitOne();*/

			logs.AppendText("got past the lock the game shall start now !\n");
			int q = 0;

			foreach (var pl in gaming_client_names)
			{
				player_scores[pl] = 0.0f; // st the score to 0
			}

			//broadcasting questions to the users
			bool some_one_disconnected = false;
			bool only_one_client_remaining = false;

			int clientCounter = 0;
			Thread.Sleep(1500);
			while (question_num > 0 && !only_one_client_remaining)
			{
				String this_question = lines[(2 * q) % (lines.Length)];
				//debug_logs.AppendText("lines.Length :" + lines.Length  + "(2 * q) % (lines.Length ) =  " + (2 * q) % (lines.Length ) );
				this_question = "QUEST" + this_question + "\n";
				broadcast(this_question);
				// Get the user answers
				// Wait for all the player threads
				//sem.WaitOne();
				//sem.WaitOne();
				foreach (Socket soc in gaming_client_sockets)
				{
					string clientName = socket_to_name[soc];
					//check if clientName is in gaming_client_names so that only people who joined before game started can play the game.
					if (gaming_client_names.Contains(clientName))
					{

						try
						{
							//Burasi tam receive de blockalmadan once if else le checkleyelim 
							Byte[] buffer = new Byte[64];
							soc.Receive(buffer);
							string incomingMessage = Encoding.Default.GetString(buffer);
							incomingMessage = incomingMessage.Substring(0, incomingMessage.IndexOf("\0"));
							clientCounter++;

							logs.AppendText("Client " + clientName + " : " + incomingMessage + "\n");

							int clients_ans;
							if (Int32.TryParse(incomingMessage, out clients_ans))
							{
								name_to_answer[clientName] = clients_ans;
							}
							else
							{
								logs.AppendText("something went very wrong number should have been send from client \n");
							}
						}
						catch
						{
							// One user terminated, other user should win the game
							if (!terminating)
							{
								logs.AppendText("A client " + clientName + " has disconnected\n");
								client_names.Remove(clientName);
								//client_sockets.Remove(soc);
								//num_of_players--;
								//remove soc from client_sockets
								//client_sockets.Remove(soc);
								//remove clientName from client_names
								//client_names.Remove(clientName);
								//remove clientName from name_to_answer
								//name_to_answer.Remove(clientName);
								//remove soc from socket_to_name
								//socket_to_name.Remove(soc);
								//remove clientName from player_scores
								//player_scores.Remove(clientName);

							}
							name_to_answer[clientName] = -1;
							try
							{
								soc.Close();
							}
							catch
							{

							}
							//client_sockets.Remove(thisClient);
							//client_names.Remove(name);
							//broadcast("User");		

						}
						finally
						{
							Thread.Sleep(250);
						}
					}
				}
				//after we got the answers

				//some_one_disconnected = false;

				if (only_one_client_remaining)
				{
					logs.AppendText("Only one client remaining, game over\n");
					break;
				}

				String disconnected_players_name = "";
				List<Socket> discon_socs = new List<Socket>();
				foreach (var cl in client_sockets)
				{
					debug_logs.AppendText("carsh : " + client_sockets.Count());
					if (!cl.Connected)
					{
						//some_one_disconnected = true;
						disconnected_players_name = socket_to_name[cl];
						broadcast("DCPLY" + disconnected_players_name + " has disconnected.\n");
						if (gaming_client_names.Contains(disconnected_players_name))
						{
							player_scores[disconnected_players_name] = 0.0f;
							gaming_client_names.Remove(disconnected_players_name);
							if (!observer_names.Contains(disconnected_players_name))
							{
								client_names.Remove(disconnected_players_name);
							}
							//client_sockets.Remove(cl);
							//add cl socket to discon_socs socket list
							discon_socs.Add(cl);

						}
						//if someone disconnect we wont break the loop unless there is only one person still playing
						if (gaming_client_names.Count() == 1)
						{
							only_one_client_remaining = true;
							broadcast("DCPLY" + "You are the only person left in the game, you win by default!\n");
							break;
						}

					}
				}

				//now remove from client sockets
				foreach (var cl in discon_socs)
				{
					//if a gamer need to remove it too
					if (gaming_client_sockets.Contains(cl))
					{
						gaming_client_sockets.Remove(cl);

					}
					client_sockets.Remove(cl);
				}


				Dictionary<string, int> name_dif = new Dictionary<string, int>();
				bool is_a_tie = false;
				List<String> winner_clients = new List<String>();
				String winner_client_name = "";
				String tmp_round_winner = "";

				//checking clients' answers and saving the real answer-client answer differences
				foreach (string client_name in gaming_client_names)
				{
					int answer;
					if (Int32.TryParse(lines[(2 * q) % (lines.Length) + 1], out answer))
					{
						int client_answer = name_to_answer[client_name];
						int difference = Math.Abs(answer - client_answer);
						name_dif[client_name] = difference;
					}
				}
				//if all values in name_dif are equal to each other then update the player scores by increasing them all by 0.5

				if (name_dif.Values.Distinct().Count() == 1)
				{
					foreach (string client_name in gaming_client_names)
					{
						// Niye cevap her zaman 0 geliyor ?
						player_scores[client_name] += 1.0f / gaming_client_names.Count();
					}
					is_a_tie = true;
				}
				else //its not a tie so will increase the max value with one
				{
					// Sort the difference dictionary to pull out the max score.
					var sortedDict = from entry in name_dif orderby entry.Value ascending select entry;
					int max_score = sortedDict.First().Value;
					int same_answer_counter = 0;

					foreach(int value in name_dif.Values)
					{
						if (value == max_score)
							same_answer_counter++;
					}

					if (same_answer_counter > 1)
						is_a_tie = true;

					// magic !
					var keys = sortedDict.Where(x => x.Value == max_score).Select(x => x.Key);
					// Update the player scores

					foreach(var key in keys)
					{
						player_scores[key] += 1.0f / same_answer_counter;
					}

					if(!is_a_tie)
					{
						winner_client_name = keys.First();
					}
					else
					{
						foreach(var key in keys)
						{
							winner_clients.Add(key);
						}
					}
					/*
					foreach (String Pl in keys)
					{
						//since the first one is the top
						player_scores[Pl] += 1.0f;
						break;
					}
					*/

				}

				if (!is_a_tie || only_one_client_remaining)
				{
					tmp_round_winner = winner_client_name + " is the winner of the round!";
				}
				else if (is_a_tie && name_dif.Values.Distinct().Count() != 1)
				{
					tmp_round_winner = "This round it is a tie for:";
					foreach(var key in winner_clients)
					{
						tmp_round_winner += key + ", ";
					}
				}
				else
				{
					tmp_round_winner = "This round it is a tie for everyone.";
				}

				// Concatenate the player name with their answer and broadcast it to the each client
				String answare_info = "Answers: real : " + lines[(2 * q) % (lines.Length) + 1] + "\n";
				foreach (var pl in gaming_client_names)
				{
					answare_info += pl + " : " + name_to_answer[pl] + " ";
				}
				answare_info += "\n";

				broadcast("ANSWE" + answare_info);

				// Concatenate the player with their associated score and broadcast it to the each client

				String score_info = "Current scores: ";
				//add player_scores[pl] for each pl to score_info in descending order
				var sortedscores = from entry in player_scores orderby entry.Value descending select entry;
				foreach (var pl in sortedscores)
				{
					score_info += pl.Key + " : " + pl.Value + " ";
				}


				//foreach (var pl in gaming_client_names)
				//{
				//	score_info += pl + ": " + player_scores[pl] + " ";

				//}
				score_info += "\n" + tmp_round_winner + "\n";
				broadcast("SCORE" + score_info);

				question_num--;
				q++;
			}

			//after the while loop is over and all question and value stuff is done.

			var sortedDict2 = from entry in player_scores orderby entry.Value descending select entry;
			float max_scores = sortedDict2.First().Value;
			var winner_keys = sortedDict2.Where(x => x.Value == max_scores).Select(x => x.Key);

			String end_of_game = "The game has ended !" + "\n ";

			if (winner_keys.Count() > 1)
			{
				if (!only_one_client_remaining)
				{
					end_of_game += "It is a tie!\n";
					end_of_game += "";
				}

				foreach (String winner in winner_keys)
				{
					end_of_game += winner + " with a score of " + sortedDict2.First().Value + "\n";
				}
				broadcast("TIEGO" + end_of_game + "\n");
			}
			else
			{
				end_of_game += "The winner is " + sortedDict2.First().Key + " with a score of " + sortedDict2.First().Value + "\n";
				broadcast("GMOVR" + end_of_game + "\n");
			}

			Thread.Sleep(1000);
			clean_after_game();
		}

		private void clean_after_game()
		{
			//num_of_players = 0;
			game_started = false;
			/*
			foreach (Socket cl in client_sockets)
			{
				cl.Close();
			}
			
			foreach (Thread t in current_threads)
			{
				t.Join();
			}
			*/
			terminating = false;
			//listening = false;
			question = false;
			observer_names = new List<String>();

			//max_num_of_clients = 2;
			//num_of_players = 0;

			/*
			client_sockets = new List<Socket>();
			client_names = new List<String>();
			*/

			// first_sem = new // Semaphore(0, 3); //  for step one 3 is known 
			// sem = new // Semaphore(0, 2); // 2 is the number of players 
			Start_game.Enabled = true;

			player_scores = new Dictionary<String, float>();
			name_to_answer = new Dictionary<String, int>();
			gaming_client_names = new List<String>(client_names);
			gaming_client_sockets = new List<Socket>(client_sockets);

			foreach (Socket sc in gaming_client_sockets)
			{
				Thread check_user_thread = new Thread(() => check_user(sc));
				check_user_thread.Name = "check_user_thread";
				check_user_thread.Start();
			};
			/*
			socket_to_name = new Dictionary<Socket, String>();
			*/

			//Thread game_loop_thread = new Thread(game_loop);
			//game_loop_thread.Start();
		}

		private void Set_question_number_Click(object sender, EventArgs e)
		{
			if (Int32.TryParse(number_of_questions.Text, out question_num))
			{
				//reads all lines and stores all lines in string array
				gaming_client_names = new List<String>(client_names);
				gaming_client_sockets = new List<Socket>(client_sockets);
				List<Socket> disconnected_clients = new List<Socket>();
				foreach (Socket client in client_sockets)
				{
					if (!client.Connected)
					{
						disconnected_clients.Add(client);

					}
				}
				//remove them
				foreach (Socket client in disconnected_clients)
				{
					client_names.Remove(socket_to_name[client]);
					gaming_client_names.Remove(socket_to_name[client]);
					gaming_client_sockets.Remove(client);
					socket_to_name.Remove(client);
					client_sockets.Remove(client);
				}
				//first_sem.Release();//#UP
				if (client_sockets.Count() < 2)
				{
					debug_logs.AppendText("Not enough players, there are currently " + client_sockets.Count() + " players \n");
				}
				else
				{


					lines = readFile("questions.txt");
					question = true;
					//Start_game.Enabled = false;
					logs.AppendText("number of questions: " + question_num + "\n");
					game_started = true;
					Thread game_loop_thread = new Thread(game_loop);
					game_loop_thread.Name = "game_loop_thread";

					game_loop_thread.Start();
					Start_game.Enabled = false;
				}

			}
			else
			{
				logs.AppendText("Please check question number \n");
			}
		}

		private void debug_logs_TextChanged(object sender, EventArgs e)
		{

		}
	}
}
