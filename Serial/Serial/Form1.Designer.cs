namespace Serial
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
            this.components = new System.ComponentModel.Container();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.btn_connect = new System.Windows.Forms.Button();
            this.cmb_name = new System.Windows.Forms.ComboBox();
            this.lb_status = new System.Windows.Forms.Label();
            this.btn_disconnect = new System.Windows.Forms.Button();
            this.lb_data_arduino = new System.Windows.Forms.Label();
            this.txt_dem = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_set = new System.Windows.Forms.TextBox();
            this.btn_set = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // serialPort
            // 
            this.serialPort.PortName = "COM10";
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // btn_connect
            // 
            this.btn_connect.Location = new System.Drawing.Point(107, 192);
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.Size = new System.Drawing.Size(75, 23);
            this.btn_connect.TabIndex = 0;
            this.btn_connect.Text = "Connect";
            this.btn_connect.UseVisualStyleBackColor = true;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // cmb_name
            // 
            this.cmb_name.FormattingEnabled = true;
            this.cmb_name.Location = new System.Drawing.Point(201, 212);
            this.cmb_name.Name = "cmb_name";
            this.cmb_name.Size = new System.Drawing.Size(95, 21);
            this.cmb_name.TabIndex = 1;
            // 
            // lb_status
            // 
            this.lb_status.AutoSize = true;
            this.lb_status.Location = new System.Drawing.Point(350, 215);
            this.lb_status.Name = "lb_status";
            this.lb_status.Size = new System.Drawing.Size(0, 13);
            this.lb_status.TabIndex = 2;
            // 
            // btn_disconnect
            // 
            this.btn_disconnect.Location = new System.Drawing.Point(107, 226);
            this.btn_disconnect.Name = "btn_disconnect";
            this.btn_disconnect.Size = new System.Drawing.Size(75, 23);
            this.btn_disconnect.TabIndex = 3;
            this.btn_disconnect.Text = "Disconnect";
            this.btn_disconnect.UseVisualStyleBackColor = true;
            this.btn_disconnect.Click += new System.EventHandler(this.btn_disconnect_Click);
            // 
            // lb_data_arduino
            // 
            this.lb_data_arduino.AutoSize = true;
            this.lb_data_arduino.Location = new System.Drawing.Point(156, 61);
            this.lb_data_arduino.Name = "lb_data_arduino";
            this.lb_data_arduino.Size = new System.Drawing.Size(0, 13);
            this.lb_data_arduino.TabIndex = 4;
            // 
            // txt_dem
            // 
            this.txt_dem.Location = new System.Drawing.Point(135, 96);
            this.txt_dem.Name = "txt_dem";
            this.txt_dem.Size = new System.Drawing.Size(100, 20);
            this.txt_dem.TabIndex = 5;
            this.txt_dem.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(59, 99);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Số đếm";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(260, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Số set";
            // 
            // txt_set
            // 
            this.txt_set.Location = new System.Drawing.Point(303, 96);
            this.txt_set.Name = "txt_set";
            this.txt_set.Size = new System.Drawing.Size(100, 20);
            this.txt_set.TabIndex = 8;
            // 
            // btn_set
            // 
            this.btn_set.Location = new System.Drawing.Point(303, 122);
            this.btn_set.Name = "btn_set";
            this.btn_set.Size = new System.Drawing.Size(75, 23);
            this.btn_set.TabIndex = 9;
            this.btn_set.Text = "Set";
            this.btn_set.UseVisualStyleBackColor = true;
            this.btn_set.Click += new System.EventHandler(this.btn_set_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 261);
            this.Controls.Add(this.btn_set);
            this.Controls.Add(this.txt_set);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_dem);
            this.Controls.Add(this.lb_data_arduino);
            this.Controls.Add(this.btn_disconnect);
            this.Controls.Add(this.lb_status);
            this.Controls.Add(this.cmb_name);
            this.Controls.Add(this.btn_connect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.ComboBox cmb_name;
        private System.Windows.Forms.Label lb_status;
        private System.Windows.Forms.Button btn_disconnect;
        private System.Windows.Forms.Label lb_data_arduino;
        private System.Windows.Forms.TextBox txt_dem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_set;
        private System.Windows.Forms.Button btn_set;
    }
}

