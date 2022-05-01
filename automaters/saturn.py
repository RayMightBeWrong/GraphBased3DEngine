import math, random

f = open("saturn.xml", 'w')

angle = 0
inc = 2 * math.pi / 80
radius = 22
random.seed(2)

def scale(i):
    if i in [10, 14]:
        f.write('\t\t\t\t\t\t\t<scale x="0.06" y="0.06" z="0.06"/>\n')
    elif i == 15:
        f.write('\t\t\t\t\t\t\t<scale x="0.16" y="0.16" z="0.16"/>\n')
    elif i in [16, 70]:
        f.write('\t\t\t\t\t\t\t<scale x="0.18" y="0.18" z="0.18"/>\n')
    elif i in [21, 60]:
        f.write('\t\t\t\t\t\t\t<scale x="0.24" y="0.24" z="0.24"/>\n')
    elif i == 40:
        f.write('\t\t\t\t\t\t\t<scale x="0.80" y="0.80" z="0.80"/>\n')
    else:
        f.write('\t\t\t\t\t\t\t<scale x="0.05" y="0.05" z="0.05"/>\n')

def buildTranslate(i, x, y, z):
    args = [0, 0, 0, 0]
    if i % 2 == 0:
        args[0] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(x)}" y="{"{:.2f}".format(y)}" z="0"/>\n'
        args[1] = f'\t\t\t\t\t\t\t\t<point x="0" y="0" z="{"{:.2f}".format(z)}"/>\n'
        args[2] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(-x)}" y="{"{:.2f}".format(-y)}" z="0"/>\n'
        args[3] = f'\t\t\t\t\t\t\t\t<point x="0" y="0" z="{"{:.2f}".format(-z)}"/>\n'
    else:
        args[0] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(y)}" z="{"{:.2f}".format(z)}"/>\n'
        args[1] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(x)}" y="0" z="0"/>\n'
        args[2] = f'\t\t\t\t\t\t\t\t<point x="0" y="{"{:.2f}".format(-y)}" z="{"{:.2f}".format(-z)}"/>\n'
        args[3] = f'\t\t\t\t\t\t\t\t<point x="{"{:.2f}".format(-x)}" y="0" z="0"/>\n'
    return args

def translate(i, time, args):
    i1 = i % 4
    i2 = (i1 + 1) % 4
    i3 = (i1 + 2) % 4
    i4 = (i1 + 3) % 4

    f.write(f'\t\t\t\t\t\t\t<translate time = "{time}" align="False">\n')
    f.write(args[i1])
    f.write(args[i2])
    f.write(args[i3])
    f.write(args[i4])
    f.write('\t\t\t\t\t\t\t</translate>\n')


f.write('\t\t\t\t<group>\n')
for i in range(1, 84):
    f.write('\t\t\t\t\t<!-- #S' + str(i) + ' -->\n')
    f.write('\t\t\t\t\t<group>\n')
    f.write('\t\t\t\t\t\t<models>\n')
    f.write('\t\t\t\t\t\t\t<model file="sphere.3d" /> <!-- generator sphere 1 20 20 sphere.3d -->\n')
    f.write('\t\t\t\t\t\t</models>\n')
    f.write('\t\t\t\t\t\t<transform>\n')
    x = radius * math.sin(angle)
    y = random.randint(-10, 10)
    z = radius * math.cos(angle)
    time = random.randint(10, 100)
    args = buildTranslate(i, x, y, z)
    translate(i, time, args)
    scale(i)
    angle += inc
    f.write('\t\t\t\t\t\t</transform>\n')
    f.write('\t\t\t\t\t</group>\n\n')
f.write('\t\t\t\t</group>\n')

