import clsx from 'clsx';
import Heading from '@theme/Heading';
import styles from './styles.module.css';

const FeatureList = [
  {
    title: '🚀 Easy to Set Up, Simple to Operate',
    Svg: require('@site/static/img/undraw_docusaurus_mountain.svg').default,
    description: (
      <>
        AIR-WALL was designed from the ground up to be easily installed and operated, allowing users to quickly deploy, configure, and monitor their IoT-based network wall through an intuitive interface and minimal hardware setup.
      </>
    ),
  },
  {
    title: '🎯 Focus on What Matters',
    Svg: require('@site/static/img/undraw_docusaurus_tree.svg').default,
    description: (
      <>
        AIR-WALL lets you focus on securing and monitoring your IoT environment—we handle the background processes. From Wi-Fi configuration to real-time dashboard monitoring, everything is streamlined so you can spend more time using the device, not setting it up.
      </>
    ),
  },
  {
    title: '⚛️ Powered by ESP32 & Web Interface',
    Svg: require('@site/static/img/undraw_docusaurus_react.svg').default,
    description: (
      <>
        AIR-WALL combines the power of ESP32 with a responsive web dashboard to provide real-time control and monitoring. The interface is lightweight, extendable, and designed to deliver a smooth user experience—whether you're switching modes or checking logs.
      </>
    ),
  },
];

function Feature({Svg, title, description}) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center">
        <Svg className={styles.featureSvg} role="img" />
      </div>
      <div className="text--center padding-horiz--md">
        <Heading as="h3">{title}</Heading>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
