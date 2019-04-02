import smtplib
from email import encoders
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart
from tkinter import *
from tkinter.messagebox import *
import _email
class emailapp:
	def __init__(self):
		self.sender = '1332372004@qq.com'
		self.password = "eijppwaapjrbbaah"
		self.msg = MIMEMultipart()

		self.tk = Tk()
		self.tk.title('代发email_app')
		self.receivers = StringVar()
		self.subject = StringVar()
		self.text = StringVar()
		self.text.set('在此输入内容')
		Label(self.tk,text='收件人：').grid(row=0,column=0,sticky=W)
		Label(self.tk,text='主题：').grid(row=1,column=0,sticky=W)
		Label(self.tk, text='正文：').grid(row=2, column=0, sticky=W)
		self.e1 = Entry(self.tk,textvariable=self.receivers)
		self.e1.grid(row=0,column=1,columnspan=3)
		self.e2 = Entry(self.tk, textvariable=self.subject)
		self.e2.grid(row=1, column=1, columnspan=3)
		self.e3 = Entry(self.tk, textvariable=self.text)
		self.e3.grid(row=2, column=1, columnspan=3)
		self.b = Button(self.tk,text='发送',command=self.send)
		self.b.grid(row=3,column=3)
		self.tk.protocol('WM_DELETE_WINDOW',self.QUIT)
	def send(self):
		try:
			self.msg['Subject'] = self.subject
			# 发送方信息
			self.msg['From'] = self.sender
			# 邮件正文是MIMEText:
			self.msg_content = self.text
			self.msg.attach(MIMEText(self.msg_content, 'plain', 'utf-8'))
			# QQsmtp服务器的端口号为465或587
			s = smtplib.SMTP_SSL("smtp.qq.com ", 465)
			s.set_debuglevel(1)
			s.login(self.sender, self.passWord)
			# 给receivers列表中的联系人逐个发送邮件
			for i in range(len([self.receivers,])):
				to = self.receivers[i]
				self.msg['To'] = to
				s.sendmail(self.sender, to, self.msg.as_string())
				print('Success!')
			s.quit()
			print("All emails have been sent over!")
		except smtplib.SMTPException as e:
			print("Falied,%s", e)

	def QUIT(self):
		if askokcancel("quit",'do you want to close it?'):
			self.tk.quit()
			self.tk.destroy()
	def com_ms(self):
		return [self.receivers,],self.subject,self.text
class Email:
	def __init__(self,r,s,t):
		self.sender = '1332372004@qq.com'
		self.password = "eijppwaapjrbbaah"
		self.receivers = r
		self.subject = s
		self.text = t
