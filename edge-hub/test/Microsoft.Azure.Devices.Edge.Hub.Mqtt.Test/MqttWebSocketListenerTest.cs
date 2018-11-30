// Copyright (c) Microsoft. All rights reserved.
namespace Microsoft.Azure.Devices.Edge.Hub.Mqtt.Test
{
    using DotNetty.Buffers;
    using Microsoft.Azure.Devices.Edge.Hub.Core.Identity;
    using Microsoft.Azure.Devices.Edge.Util.Test.Common;
    using Microsoft.Azure.Devices.ProtocolGateway;
    using Microsoft.Azure.Devices.ProtocolGateway.Identity;
    using Microsoft.Azure.Devices.ProtocolGateway.Messaging;
    using Microsoft.Azure.Devices.ProtocolGateway.Mqtt.Persistence;
    using Moq;
    using System.Threading.Tasks;
    using Xunit;

    [Unit]
    public class MqttWebSocketListenerTest
    {
        [Fact]
        public void ReturnsMqttSubProtocol()
        {
            var listener = new MqttWebSocketListener(
                new ProtocolGateway.Mqtt.Settings(Mock.Of<ISettingsProvider>()),
                id => Task.FromResult(Mock.Of<IMessagingBridge>()),
                Mock.Of<Microsoft.Azure.Devices.Edge.Hub.Core.IAuthenticator>(),
                Mock.Of<IClientCredentialsFactory>(),
                () => Mock.Of<ISessionStatePersistenceProvider>(),
                new DotNetty.Transport.Channels.MultithreadEventLoopGroup(),
                Mock.Of<IByteBufferAllocator>(),
                false,
                0);

            Assert.Equal(Constants.WebSocketSubProtocol, listener.SubProtocol);
        }
    }
}
