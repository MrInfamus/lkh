import matplotlib.pyplot as plt

lkhfile = open("../tmp/lkh_out.txt", "r")
safile = open("../tmp/sa_out.txt", "r")

#print(lkhfile.read().split('\n'))
lkhstr = list(map(lambda x: x.split('\t'), lkhfile.read().split('\n')))
sastr = list(map(lambda x: x.split('\t'), safile.read().split('\n')))

lkhfile.close()
safile.close()

#print(lkhstr)
#plt.style.use('_mpl-gallery')
fig, ax = plt.subplots()

x = []
y = []
t = -1
te = 9
for i in range(len(sastr)):
	if sastr[i] == ['']:
		t+=1
		if(t == te):
			ax.plot(x, y, linewidth=2.0, color="black")
			break
		x = []
		y = []
		continue

	x.append(float(sastr[i][1]))
	y.append(float(sastr[i][0]))
#plt.show()
x = []
y = []
t = -1
for i in range(len(lkhstr)):
	if lkhstr[i] == ['']:
		print(x, y)
		t+=1
		if(t == te):
			ax.plot(x, y, linewidth=2.0, color="red")
			break
		x = []
		y = []
		continue
	x.append(float(lkhstr[i][1]))
	y.append(float(lkhstr[i][0]))
#ax.plot(x, y, linewidth=2.0, color='green')

plt.show()