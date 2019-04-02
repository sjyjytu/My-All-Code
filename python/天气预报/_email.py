import smtplib
from email import encoders
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart

class Email:
	def __init__(self,r,s,t):
		self.sender = '1332372004@qq.com'
		self.password = "eijppwaapjrbbaah"
		self.receivers = r
		self.subject = s
		self.text = t
		self.msg = MIMEMultipart()
		# 邮件主题
		self.msg['Subject'] = self.subject
		# 发送方信息
		self.msg['From'] = self.sender
		# 邮件正文是MIMEText:
		self.msg_content = self.text
		self.msg.attach(MIMEText(self.msg_content, 'plain', 'utf-8'))
	def send_email(self):
		try:
			# QQsmtp服务器的端口号为465或587
			s = smtplib.SMTP_SSL("smtp.qq.com ", 465)
			s.set_debuglevel(1)
			s.login(self.sender, self.passWord)
			# 给receivers列表中的联系人逐个发送邮件
			for i in range(len(self.receivers)):
				to = self.receivers[i]
				self.msg['To'] = to
				s.sendmail(self.sender, to, self.msg.as_string())
				print('Success!')
			s.quit()
			print("All emails have been sent over!")
		except smtplib.SMTPException as e:
			print("Falied,%s", e)