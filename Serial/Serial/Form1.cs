using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

namespace Serial
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            cmb_name.DataSource = SerialPort.GetPortNames();// Quét các cổng COM đang hoạt động lên comboBox1
            this.serialPort.DataReceived +=new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            
        }

        private void btn_connect_Click(object sender, EventArgs e)//Connect to COM
        {
            try
            {
                if (!serialPort.IsOpen)
                {
                    serialPort.PortName = cmb_name.Text;
                    //serialPort.BaudRate = Convert.ToInt32(comboBox3.Text);
                    serialPort.Open();
                    lb_status.Text = ("Đã kết nối");
                    lb_status.ForeColor = Color.Green;
                }
             }

            catch
            {
                MessageBox.Show("khong the mo cong com");
            }
        }

        private void btn_disconnect_Click(object sender, EventArgs e)
        {
            serialPort.Close();
            lb_status.Text = ("Chưa kết nối");
            lb_status.ForeColor = Color.Red;
         }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
               txt_dem.Text = serialPort.ReadTo("\n");
                //txt_dem.Text = serialPort.ReadExisting();
              // String dataFromArduino = serialPort.ReadLine().ToString();
              // txt_dem.Text = dataFromArduino;
             }
            catch (Exception)
            {
                MessageBox.Show(" khong nhan duoc du lieu");
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void btn_set_Click(object sender, EventArgs e)
        {
           String soset = this.txt_set.Text;
           try
           {
               serialPort.Write(soset);
           }
           catch (Exception)
           {
               
              
           }

        }
        }
    }

