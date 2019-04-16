import tensorflow as tf
a = tf.constant(2)
with tf.Session() as sess:
   print(sess.run(a))

