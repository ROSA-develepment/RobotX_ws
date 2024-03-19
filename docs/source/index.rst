.. ROSA documentation master file, created by
   sphinx-quickstart on Mon Feb 19 18:31:26 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ROSA's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Indices and tables
==================


* :ref:`Periface`
* :ref:`Publisher`
* :ref:`modindex`
* :ref:`search`


Periface
--------
Since the objective is just to create a layer for more reusable and easyer to write code, all the main ROS features will have the same name.
In this page you'll find a guide to use it.
All examples can be found under RobotX/src/examples/

Publisher
---------
This is the example for a simple Publisher.
For this simple example, the Publisher will only publish a message, **SomeNumber**, on *number_topic*

It is declared like this:

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
