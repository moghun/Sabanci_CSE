namespace Server
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.label1 = new System.Windows.Forms.Label();
            this.port_box = new System.Windows.Forms.TextBox();
            this.logs = new System.Windows.Forms.RichTextBox();
            this.launch_button = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.number_of_questions = new System.Windows.Forms.TextBox();
            this.Start_game = new System.Windows.Forms.Button();
            this.debug_logs = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(62, 74);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Post";
            // 
            // port_box
            // 
            this.port_box.Cursor = System.Windows.Forms.Cursors.AppStarting;
            this.port_box.Location = new System.Drawing.Point(96, 67);
            this.port_box.Name = "port_box";
            this.port_box.Size = new System.Drawing.Size(100, 20);
            this.port_box.TabIndex = 1;
            this.port_box.Text = "1515";
            this.port_box.TextChanged += new System.EventHandler(this.port_box_TextChanged);
            // 
            // logs
            // 
            this.logs.Location = new System.Drawing.Point(60, 129);
            this.logs.Name = "logs";
            this.logs.Size = new System.Drawing.Size(473, 425);
            this.logs.TabIndex = 2;
            this.logs.Text = "";
            this.logs.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // launch_button
            // 
            this.launch_button.Location = new System.Drawing.Point(218, 64);
            this.launch_button.Name = "launch_button";
            this.launch_button.Size = new System.Drawing.Size(75, 23);
            this.launch_button.TabIndex = 3;
            this.launch_button.Text = "launch Server";
            this.launch_button.UseVisualStyleBackColor = true;
            this.launch_button.Click += new System.EventHandler(this.launch_button_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(57, 106);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(106, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Number of Questions";
            // 
            // number_of_questions
            // 
            this.number_of_questions.Location = new System.Drawing.Point(169, 103);
            this.number_of_questions.Name = "number_of_questions";
            this.number_of_questions.Size = new System.Drawing.Size(100, 20);
            this.number_of_questions.TabIndex = 5;
            this.number_of_questions.Text = "1";
            // 
            // Start_game
            // 
            this.Start_game.Location = new System.Drawing.Point(287, 100);
            this.Start_game.Name = "Start_game";
            this.Start_game.Size = new System.Drawing.Size(75, 23);
            this.Start_game.TabIndex = 6;
            this.Start_game.Text = "Start Game";
            this.Start_game.UseVisualStyleBackColor = true;
            this.Start_game.Click += new System.EventHandler(this.Set_question_number_Click);
            // 
            // debug_logs
            // 
            this.debug_logs.Location = new System.Drawing.Point(583, 129);
            this.debug_logs.Name = "debug_logs";
            this.debug_logs.Size = new System.Drawing.Size(410, 425);
            this.debug_logs.TabIndex = 7;
            this.debug_logs.Text = "";
            this.debug_logs.TextChanged += new System.EventHandler(this.debug_logs_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(583, 110);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "debug ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.ClientSize = new System.Drawing.Size(1019, 566);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.debug_logs);
            this.Controls.Add(this.Start_game);
            this.Controls.Add(this.number_of_questions);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.launch_button);
            this.Controls.Add(this.logs);
            this.Controls.Add(this.port_box);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox port_box;
		private System.Windows.Forms.RichTextBox logs;
		private System.Windows.Forms.Button launch_button;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox number_of_questions;
		private System.Windows.Forms.Button Start_game;
		private System.Windows.Forms.RichTextBox debug_logs;
		private System.Windows.Forms.Label label3;
	}
}

