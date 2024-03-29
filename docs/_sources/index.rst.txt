.. ROSA documentation master file, created by
    sphinx-quickstart on Mon Feb 19 18:31:26 2024.
    You can adapt this file completely to your liking, but it should at least
    contain the root `toctree` directive.

.. _examples: https://github.com/ROSA-develepment/RobotX/tree/main/src/examples/src
.. _example1: https://github.com/ROSA-develepment/RobotX_ws/tree/main/robotx/src/examples/numberpublisher
.. _example2: https://github.com/ROSA-develepment/RobotX_ws/tree/main/robotx/src/examples/numbersubscriber
.. _example3: https://github.com/ROSA-develepment/RobotX_ws/tree/main/robotx/src/examples/addtwonumbersservice
.. _example4: https://github.com/ROSA-develepment/RobotX_ws/tree/main/robotx/src/examples/addtwonumbersclient

Welcome to ROSA's documentation!
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


Indices and tables
==================


* :ref:`publisher`
* :ref:`subscriber`
* :ref:`service`
* :ref:`client`
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


.. _service:

Service
-------
Service is an abstract class, it is suposed to be derived to adapt to it's porpuse.
Like in the `example3`_ a simple service is created like so:

.. code-block:: cpp

	using SomeService = interfaces::srv::SomeService;

	class AddTwoNumbersService : public Service<SomeService>
	{
	public:
		AddTwoNumbersService(Node* parent, std::string const& service);

	private:
		void processRequest(SomeService::Request::SharedPtr request,
				SomeService::Response::SharedPtr response) override;
	};

.cpp:

.. code-block:: cpp

	AddTwoNumbersService::AddTwoNumbersService(Node *parent, std::string const& service)
		: Service(parent, service)
	{

	}

	void AddTwoNumbersService::processRequest(SomeService::Request::SharedPtr request,
                                         SomeService::Response::SharedPtr response)
	{
		response->answer = request->first + request->second;
	}

After it can be declared and initialized on a node:

.. code-block:: cpp

	class AddTwoNumbersServiceNode : public Node
	{
	public:
		AddTwoNumbersServiceNode(std::string const& name);

	private:

		AddTwoNumbersService _server;
	};

.cpp

.. code-block:: cpp

	AddTwoNumbersServiceNode::AddTwoNumbersServiceNode(std::string const &name)
		: Node(name)
		, _server(this, "add_two_numbers")
	{

	}

.. _client:

Client
------
Client is an abstract class, it's porpuse is to be derived to adapt to it's porpuse.
A request can be sent to a service like in `example4`_ for a simple Client, the request is sent to *add_two_numbers* service:

.. code-block:: cpp

	using SomeService = interfaces::srv::SomeService;

	class AddTwoNumbersClient : public Client<SomeService>
	{
	public:
		AddTwoNumbersClient(Node* parent, std::string const& serviceName);

		void setRequest(int first, int second);

	private:
		void sendRequest() override;

	};

.cpp

.. code-block:: cpp

	AddTwoNumbersClient::AddTwoNumbersClient(Node *parent, std::string const &serviceName)
		: Client(parent, serviceName)
	{

	}

	void AddTwoNumbersClient::setRequest(int first, int second)
	{
		_request->first = first;
		_request->second = second;
	}

	void AddTwoNumbersClient::sendRequest()
	{
		waitForServer(std::chrono::seconds(1), "Waiting for add_two_numbers server");

		try
		{
			asyncSendRequest();
		}
		catch (std::exception const& e)
		{
			RCLCPP_ERROR(getLogger(), "Service call failed");
		}
	}


After it can be instantiated on a node:

.. code-block:: cpp

	using SomeService =  interfaces::srv::SomeService;

	class AddTwoNumbersClientNode : public Node
	{
	public:
		AddTwoNumbersClientNode(std::string const& name);

	private:
		AddTwoNumbersClient _client;
	};

It's used like so:


.. code-block:: cpp

	AddTwoNumbersClientNode::AddTwoNumbersClientNode(std::string const &name)
		: Node(name)
		, _client(this, "add_two_numbers")
	{
		_client.setRequest(21, 21);
		_client.startWorkerThread();
	}
