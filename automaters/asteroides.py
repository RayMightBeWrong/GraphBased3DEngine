import math, random

f = open("asteroides.xml", 'w')

angle = 0
inc = 2 * math.pi / 1000
radius = 155
random.seed(2)

f.write('\t\t<group>\n')
for i in range(1, 1001):
    f.write('\t\t\t<!-- #A' + str(i) + ' -->\n')
    f.write('\t\t\t<group>\n')
    f.write('\t\t\t\t<models>\n')
    f.write('\t\t\t\t\t<model file="sphere.3d" /> <!-- generator sphere 1 20 20 sphere.3d -->\n')
    f.write('\t\t\t\t</models>\n')
    f.write('\t\t\t\t<transform>\n')
    dist = random.randint(0, 20)
    x = (radius + dist) * math.sin(angle)
    y = random.randint(-15, 15)
    z = (radius + dist) * math.cos(angle)
    f.write(f'\t\t\t\t\t<translate x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y)}" z="{"{:.2f}".format(z)}" />\n')
    if (i % 3) == 0:
        f.write('\t\t\t\t\t<scale x="0.03" y="0.03" z="0.03" />\n')
    elif (i % 3) == 1:
        f.write('\t\t\t\t\t<scale x="0.04" y="0.04" z="0.04" />\n')
    else:
        f.write('\t\t\t\t\t<scale x="0.05" y="0.05" z="0.05" />\n')
    f.write('\t\t\t\t</transform>\n')
    angle += inc
    f.write('\t\t\t</group>\n\n')
f.write('\t\t</group>\n')
    
f.close()
