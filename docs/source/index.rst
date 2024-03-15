.. ROSA documentation master file, created by
   sphinx-quickstart on Mon Feb 19 18:31:26 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ROSA's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Something to add to documentation here


Indices and tables
==================


* :ref:`Periface`
* :ref:`Subscriber`
* :ref:`modindex`
* :ref:`search`


Periface
--------
Since the objective is just to create a layer for more reusable and easyer to write code, all the main ROS features will have the same name.
In this page you'll find a guide to use it.


Subscriber
----------

You can find the reference code under RobotX/src/closedmessageloop

This is a simple form of the subscriber. As you may know, a subscriber listens to messages on a subscribed topic

You need to declare it as a template with the type of the message to which it will listen to





.. code-block:: cpp
    
	class ClosedMessageLoopNode : public Node
	{
	public:
    	ClosedMessageLoopNode(std::string const& name);

    	void sendMessage();

	private:
    	void messageCallback(interfaces::msg::SomeMessage::SharedPtr const& message);

    	Subscriber<interfaces::msg::SomeMessage> _someMessageSubscriber;

    	std::string _someMessage;
    	int _someMessageReference;
	};


This way you can 