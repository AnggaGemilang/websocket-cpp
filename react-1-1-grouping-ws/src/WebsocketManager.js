import React, { useState, useRef, useEffect, useCallback } from "react";

const WebSocketManager = () => {
  const [messages, setMessages] = useState({});
  const connections = useRef({});

  const handleNewMessage = useCallback((id, data) => {
    setMessages((prevMessages) => ({
      ...prevMessages,
      [id]: data,
    }));
  }, []);

  useEffect(() => {
    for (let i = 0; i <= 99; i++) {
      const startTime = performance.now();

      const endpoint = `ws://localhost:${i < 10 ? "700" + i : "70" + i}/endpoint${i + 1}`;
      const ws = new WebSocket(endpoint);

      ws.onopen = () => {
        console.log(`WebSocket ${i} connected`);
        const endTime = performance.now();
        
        console.log(`Start: ${startTime}`)
        console.log(`End: ${endTime}`)
        console.log("======================")
      }
      ws.onmessage = (event) => {
        console.log(`Message from WebSocket ${i}:`, event.data);
        handleNewMessage(i, event.data);
      };
      ws.onerror = (error) => console.error(`WebSocket ${i} error:`, error);
      ws.onclose = () => console.log(`WebSocket ${i} closed`);

      connections.current[i] = ws;
    }

    return () => {
      Object.values(connections.current).forEach((ws) => ws.close());
    };
  }, [handleNewMessage]);

  return (
    <div style={{ padding: "20px" }}>
      <h1>Data 1-1-grouping-ws (7xxx) WebSocket</h1>

      <div
        style={{
          display: "grid",
          gridTemplateColumns: "repeat(auto-fit, minmax(300px, 1fr))",
          gap: "20px",
        }}
      >
        {Array.from({ length: 100 }, (_, i) => i).map((id) => (
          <div
            key={id}
            style={{
              border: "1px solid #ddd",
              borderRadius: "5px",
              padding: "10px",
            }}
          >
            <h3 style={{ margin: "0 0 10px" }}>WebSocket {id + 1}</h3>
            <div
              style={{
                background: "#f9f9f9",
                padding: "5px",
                borderRadius: "3px",
                wordWrap: "break-word",
              }}
            >
              {messages[id] || "NULL"}
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default WebSocketManager;
