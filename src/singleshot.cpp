#include "singleshot.h"


SingleShot::SingleShot(Callback cb, int ms, bool autoDelete, QObject *parent) :
    QObject(parent),
    m_AutoDelete(autoDelete),
    m_CB(cb)
{
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(onTimeout()), Qt::QueuedConnection);
    m_Timer.setSingleShot(true);

    if ( ms > 0 )
    {
        start(ms);
    }
}

void SingleShot::start(int ms)
{
    m_Timer.start(ms);
}


void SingleShot::go(SingleShot::Callback cb, int ms, bool autoDelete, QObject *parent)
{
    new SingleShot(cb,ms,autoDelete, parent);
}

void SingleShot::onTimeout()
{
    if ( m_CB )
    {
        m_CB();
    }
    if ( m_AutoDelete )
    {
        deleteLater();
    }
}
