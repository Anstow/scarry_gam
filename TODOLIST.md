TODO list
=========

Jittering in Collision detection
--------------------------------

There is a weird jittering when running into walls head on, this is because we
are modelling walls as a collection of pixels and on collision we rapidly swap
between colliding with 2 different pixels.

This shouldn't be noticeable with the controller as I believe there will almost
always be a slight glide one way or the other.

Fix: When line collisions are implemented this shouldn't happen any more.


Reduce number of collision pixels
---------------------------------

Work out a way of reducing the number of pixels to collide with.

Fix: Implement line collisions?


Overlap when colliding
----------------------

At present the is a slight overlap when colliding with the pixels above and to
the left. This is because we are colliding with the top right corner of the
pixel.


Line Collision
--------------

At present the collision code only works with points. So walls are just lots of
points next to one another. Perhaps implementing colliding with lines would fix
some of the problems mentioned above and reduce the amount of work that the
collision detection system has to do.
