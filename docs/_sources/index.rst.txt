.. ROSA documentation master file, created by
sphinx-quickstart on Mon Feb 19 18:31:26 2024.
You can adapt this file completely to your liking, but it should at least
contain the root `toctree` directive.

.. _examples: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src
.. _example1: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src/numberpublisher
.. _example2: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src/numbersubscriber
.. _example3: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src/addtwonumbersclient
.. _example4: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src/addtwonumbersserver

Welcome to ROSA's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


Indices and tables
==================


* :ref:`publisher`
* :ref:`subscriber`
* :ref:`client`
* :ref:`service`
* :ref:`modindex`
* :ref:`search`


Periface
--------
Since the objective is just to create a layer for more reusable and easyer to write code, all the main ROS features will have the same name.
In this page you'll find a guide to use it.
All `examples`_ can be found under RobotX/src/examples/



.. _publisher:

Publisher
---------
In this `example1`_ for a simple Publisher, the Publisher will only publish a message, **SomeNumber**, on *number_topic*

It's declared like this:

.. code-block:: cpp

	class NumberPublisherNode : public Node
	{
	public:

	    NumberPublisherNode(std::string const& name);

	private:

 	    Publisher<SomeNumber> _publisher;
	}

It must have the name of the message it will use.
And to initialize:

.. code-block:: cpp

	NumberPublisherNode::NumberPublisherNode(std::string const &name)
	    : Node(name)
	    , _publisher(this, "number_topic")
	{

	}



The parent node pointer is necessary to initialize the publisher, and the name of the topic on which to publish

.. _subscriber:

Subscriber
----------
In this `example2`_ for a simple Subscriber, the Subscriber will only subscribe to *number_topic* listening to messages type **SomeNumber**, and logging the received messages.

It's declared like this:

.. code-block:: cpp

	NumberSubscriberNode : public Node
	{
	public:
	    NumberSubscriberNode(std::string const& name);

	private:

	    void messageHandler(SomeNumber::SharedPtr const message);

	    Subscriber<SomeNumber> _subscriber;
	};

Notice that a handler method is also declared and it receives a **SharedPtr** as argument

To initialize and subscribe to a topic:

.. code-block:: cpp

	NumberSubscriberNode::NumberSubscriberNode(std::string const &name)
	    : Node(name)
	    , _subscriber(this)
	{
	    _subscriber.subscribe("number_topic",
	        [this](auto const message)
	        {
	            messageHandler(message);
	        });
	}


.. _client:

Client
------

In this `example3`_ for a simple Client, the *number_topic* **SomeNumber**,



.. _service:

Service
-------
`example4`_
