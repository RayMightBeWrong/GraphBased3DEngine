import math, random

f = open("saturn.xml", 'w')

angle = 0
inc = 2 * math.pi / 80
radius = 22
random.seed(2)

f.write('\t\t\t\t<group>\n')
for i in range(1, 28):
    f.write('\t\t\t\t\t<!-- #J' + str(i) + ' -->\n')
    f.write('\t\t\t\t\t<group>\n')
    f.write('\t\t\t\t\t\t<models>\n')
    f.write('\t\t\t\t\t\t\t<model file="sphere.3d" /> <!-- generator sphere 1 20 20 sphere.3d -->\n')
    f.write('\t\t\t\t\t\t</models>\n')
    f.write('\t\t\t\t\t\t<transform>\n')
    x = radius * math.sin(angle)
    y = random.randint(-10, 10)
    z = radius * math.cos(angle)
    print(y)
    f.write(f'\t\t\t\t\t\t\t<translate x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y)}" z="{"{:.2f}".format(z)}" />\n')
    if i == 10:
        f.write('\t\t\t\t\t\t\t<scale x="0.06" y="0.06" z="0.06" />\n')
    elif i == 14:
        f.write('\t\t\t\t\t\t\t<scale x="0.57" y="0.57" z="0.57" />\n')
    elif i == 15 or i == 18:
        f.write('\t\t\t\t\t\t\t<scale x="0.48" y="0.48" z="0.48" />\n')
    elif i == 21 or i == 60:
        f.write('\t\t\t\t\t\t\t<scale x="0.82" y="0.82" z="0.82" />\n')
    elif i == 40:
        f.write('\t\t\t\t\t\t\t<scale x="0.75" y="0.75" z="0.75" />\n')
    else:
        f.write('\t\t\t\t\t\t\t<scale x="0.05" y="0.05" z="0.05" />\n')
    f.write('\t\t\t\t\t\t</transform>\n')
    angle += inc
    f.write('\t\t\t\t\t</group>\n\n')
f.write('\t\t\t\t</group>\n')
    
f.close()
