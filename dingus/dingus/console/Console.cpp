#include "dingus/console/Console.hpp"
#include <time.h>

using namespace dingus;

CConsoleChannel& CConsole::CON_WARNING = CConsole::getChannel("warning");
CConsoleChannel& CConsole::CON_ERROR   = CConsole::getChannel("error");


//---------------------------------------------------------------------------
// CConsole
//---------------------------------------------------------------------------
CConsole::CConsole() :
	mDefaultRenderingCtx(NULL),
	mDefaultFilter(NULL)
{
}

CConsole::~CConsole()
{
	for (TChannelList::iterator it = mChannels.begin(); it != mChannels.end(); ++it)
	{
		delete *it;
	}
}

CConsoleChannel& CConsole::openChannel(const std::string& name)
{
	CConsoleChannel* channel = NULL;

	for (TChannelList::iterator it = mChannels.begin(); it != mChannels.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			channel = *it;
			break;
		}
	}

	if (!channel)
	{
		channel = new CConsoleChannel(*this, name, mDefaultRenderingCtx, mDefaultFilter);
		mChannels.push_back(channel);
	}

	return *channel;
}

void CConsole::closeChannel(CConsoleChannel& channel)
{
	for (TChannelList::iterator it = mChannels.begin(); it != mChannels.end(); ++it)
	{
		if (*it == &channel)
		{
			delete *it;
			it = mChannels.erase(it);
			break;
		}
	}
}

void CConsole::setDefaultRenderingContext(IConsoleRenderingContext& ctx)
{
	mDefaultRenderingCtx = &ctx;

	for (TChannelList::iterator it = mChannels.begin(); it != mChannels.end(); ++it)
	{
		if ( !(*it)->getRenderingContext())
		{
			(*it)->setRenderingContext(ctx);
		}
	}
}

//---------------------------------------------------------------------------
// CConsoleChannel
//---------------------------------------------------------------------------
CConsoleChannel::CConsoleChannel(CConsole& console, const std::string& name, IConsoleRenderingContext* renderingCtx, IConsoleFilter* filter) :
	mParentConsole(console),
	mName(name),
	mRenderingCtx(renderingCtx),
	mFilter(filter),
	mWritingChannel(true),
	mLoggingTime(false)
{
}

CConsoleChannel::~CConsoleChannel()
{
}

void CConsoleChannel::write(const std::string& methodName, const std::string& message)
{
	write(message);
}

void CConsoleChannel::write(const std::string& message)
{
	if (!mRenderingCtx)
		return;

	if (mFilter && !mFilter->apply(*this, message))
		return;

	if (mLoggingTime)
	{
		time_t clockTime;
		time(&clockTime);
		const tm* t = localtime(&clockTime);
		char buf[100];
		sprintf(buf, "[dingus|%i:%i:%i] ", t->tm_hour, t->tm_min, t->tm_sec);
		mRenderingCtx->write(buf);
	}
	else
	{
		mRenderingCtx->write("[dingus] ");
	}

	if (mWritingChannel)
	{
		mRenderingCtx->write(mName + "> ");
	}

	mRenderingCtx->write(message);
	mRenderingCtx->write("\n");
}
