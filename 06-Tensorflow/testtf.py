import tensorflow as tf

print('Tensorflow version : {}'.format(tf.__version__))

a = tf.constant(2)
with tf.Session() as sess:
   print(sess.run(a))

