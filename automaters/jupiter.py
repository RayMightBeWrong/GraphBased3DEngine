import math, random

f = open("jupiter.xml", 'w')

angle = 0
inc = 2 * math.pi / 80
radius = 22
random.seed(20)

def scale(i):
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
for i in range(1, 81):
    f.write('\t\t\t\t\t<!-- #J' + str(i) + ' -->\n')
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

